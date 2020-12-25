#include <libsnark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>
#include <libsnark/gadgetlib1/pb_variable.hpp>
#include <libsnark/gadgetlib1/gadgets/basic_gadgets.hpp>
#include <fstream>
using namespace libsnark;
using namespace std;

int main (int argc, char* argv[]) {
    typedef libff::Fr<default_r1cs_gg_ppzksnark_pp> FieldT;
    typedef libff::default_ec_pp ppzksnark_ppT;

    if(argc != 2) {
        cout << "Please input the secret number." << endl;
        return -1;
    }
    int secret;
    try {
        secret = stoi(argv[1]);
    } catch (...) {
        cout << "Incorrect format. Please input an integer as a secret." << endl;
        return -1;
    }

    // Initialize the curve parameters
    default_r1cs_gg_ppzksnark_pp::init_public_params();
  
    // Create protoboard
    protoboard<FieldT> pb;

    pb_variable<FieldT> x; // the secret value
    pb_variable<FieldT> range_high; // the high value of the range
    pb_variable<FieldT> less, less_or_eq;
    
    x.allocate(pb, "x");
    range_high.allocate(pb, "range_high");
    less.allocate(pb, "less"); // must have
    less_or_eq.allocate(pb, "less_or_eq");
    
    pb.val(range_high)= 188;
    const size_t n = 10; // the size of the bits

    comparison_gadget<FieldT> cmp(pb, n, x, range_high, less, less_or_eq, "cmp");
    cmp.generate_r1cs_constraints();
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(less, 1, FieldT::one()));

    const r1cs_constraint_system<FieldT> constraint_system = pb.get_constraint_system();
    cout << "Primary (public) input: " << pb.primary_input() << endl;
    cout << "Auxiliary (private) input: " << pb.auxiliary_input() << endl;

    // Add witness values
    pb.val(x) = secret; 
    cmp.generate_r1cs_witness();
    if (!pb.is_satisfied()) {
        cout << "pb is not satisfied" << endl;
        return -1;
    }
    //load pk
    std::fstream f_pk("range_pk.raw", std::ios_base::in);
    r1cs_gg_ppzksnark_proving_key<ppzksnark_ppT> range_pk;
    f_pk >> range_pk;
    f_pk.close();
    cout << "range_pk.raw is loaded" << endl;

    // generate proof
    const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp> proof = r1cs_gg_ppzksnark_prover<default_r1cs_gg_ppzksnark_pp>(range_pk, pb.primary_input(), pb.auxiliary_input());
    // save the proof
    std::fstream pr("range_proof.raw", std::ios_base::out);
    pr << proof;
    pr.close();
    cout << "range_proof.raw is exported" << endl;

    return 0;
}
