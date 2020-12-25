#include <libsnark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>
#include <libsnark/gadgetlib1/pb_variable.hpp>
#include <libsnark/gadgetlib1/gadgets/basic_gadgets.hpp>
#include <fstream>
using namespace libsnark;
using namespace std;

int main () {
    typedef libff::Fr<default_r1cs_gg_ppzksnark_pp> FieldT;
    typedef libff::default_ec_pp ppzksnark_ppT;

    // Initialize the curve parameters
    default_r1cs_gg_ppzksnark_pp::init_public_params();
    // Create protoboard
    protoboard<FieldT> pb;

    // load vk
    std::fstream f_vk("range_vk.raw", std::ios_base::in);
    r1cs_gg_ppzksnark_verification_key<ppzksnark_ppT> range_vk;
    f_vk >> range_vk;
    f_vk.close();
    cout << "range_vk.raw is loaded" << endl;

    // load proof
    std::fstream f_proof("range_proof.raw", std::ios_base::in);
    r1cs_gg_ppzksnark_proof<ppzksnark_ppT> range_proof;
    f_proof >> range_proof;
    f_proof.close();
    cout << "range_proof.raw is loaded" << endl;

    // verify
    bool verified = r1cs_gg_ppzksnark_verifier_strong_IC<default_r1cs_gg_ppzksnark_pp>(range_vk, pb.primary_input(), range_proof);

    cout << "Primary (public) input: " << pb.primary_input() << endl;
    cout << "Verification status: " << verified << endl;

    return 0;
}
