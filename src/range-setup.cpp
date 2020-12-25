#include <libsnark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>
#include <libsnark/gadgetlib1/pb_variable.hpp>
#include <libsnark/gadgetlib1/gadgets/basic_gadgets.hpp>
#include <fstream>
using namespace libsnark;
using namespace std;

int main () {
    typedef libff::Fr<default_r1cs_gg_ppzksnark_pp> FieldT;

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

    // generate keypair
    const r1cs_gg_ppzksnark_keypair<default_r1cs_gg_ppzksnark_pp> keypair = r1cs_gg_ppzksnark_generator<default_r1cs_gg_ppzksnark_pp>(constraint_system);
    
    // save the pk and vk to local file
    std::fstream pk("range_pk.raw", std::ios_base::out);
    pk << keypair.pk;
    pk.close();
    cout << "range_pk.raw is exported" << endl;
    std::fstream vk("range_vk.raw", std::ios_base::out);
    vk << keypair.vk;
    vk.close();
    cout << "range_vk.raw is exported" << endl;

    cout << "Number of R1CS constraints: " << constraint_system.num_constraints() << endl;

    return 0;
}
