// Testing chained rotations with quaternions (only)

#include <sm/quaternion>
#include <sm/vec>
#include <sm/mathconst>

#ifndef FLT
typedef float F;
#else
typedef FLT   F;
#endif

int main()
{
    int rtn = 0;

    using mc = sm::mathconst<F>;

    constexpr sm::vec<F> ux = { 1, 0, 0 };
    constexpr sm::vec<F> uy = { 0, 1, 0 };
    constexpr sm::vec<F> uz = { 0, 0, 1 };
    //constexpr sm::vec<F> minus_ux = { -1, 0, 0 };
    //constexpr sm::vec<F> minus_uy = { 0, -1, 0 };
    //constexpr sm::vec<F> minus_uz = { 0, 0, -1 };

    // Expected rotations
    constexpr sm::vec<F> ux_after_q1_truth = { mc::one_over_root_2, 0, mc::one_over_root_2 };
    constexpr sm::vec<F> ux_after_q2_truth = uy;
    constexpr sm::vec<F> ux_after_q1_q2_truth = { 0, mc::one_over_root_2, mc::one_over_root_2 };

    sm::quaternion<F> q1 (uy, -mc::pi_over_4);
    sm::quaternion<F> q2 (uz, mc::pi_over_2);
    // Combined rotation; first q1, then q2.
    sm::quaternion<F> q1q2 = q1 * q2;
    sm::quaternion<F> q2q1 = q2 * q1;
    sm::quaternion<F> q1premultq2 = q1;
    q1premultq2.premultiply(q2);
    sm::quaternion<F> q1postmultq2 = q1;
    q1postmultq2.postmultiply(q2);

    sm::vec<F> ux_after_q1 = q1 * ux;
    std::cout << "ux " << ux << " after rotation q1: " << ux_after_q1 << " CF: " << ux_after_q1_truth << std::endl;

    if ((ux_after_q1 - ux_after_q1_truth).abs().max() > std::numeric_limits<F>::epsilon()) {
        std::cout << "Fail 1\n";
        --rtn;
    }

    sm::vec<F> ux_after_q2 = q2 * ux;
    std::cout << "ux " << ux << " after rotation q2: " << ux_after_q2 << " CF: " << ux_after_q2_truth << std::endl;
    if ((ux_after_q2 - ux_after_q2_truth).abs().max() > std::numeric_limits<F>::epsilon()) {
        std::cout << "Fail 2\n";
        --rtn;
    }

    // Fails, as expected. Equivalent to q1 * (q2 * ux) i.e. q2 * ux FIRST, THEN rotate by q1, which is not the target order of rotations
    sm::vec<F> ux_after_q1_q2 = q1 * q2 * ux;
    if ((ux_after_q1_q2 - ux_after_q1_q2_truth).abs().max() > std::numeric_limits<F>::epsilon()) {
        std::cout << "q1_q2 fails as expected\n";
    } else {
        std::cout << "Fail 3. q1_q2 is expected to fail but didn't\n";
        --rtn;
    }

    // Should not fail
    sm::vec<F> ux_after_q2_q1 = q2 * q1 * ux;
    std::cout << "ux " << ux << " after rotation q2 * q1: " << ux_after_q2_q1 << " CF: " << ux_after_q1_q2_truth << std::endl;
    if ((ux_after_q2_q1 - ux_after_q1_q2_truth).abs().max() > std::numeric_limits<F>::epsilon()) {
        std::cout << "Fail 3.1 q2_q1\n";
        --rtn;
    }

    sm::vec<F> ux_after_q1_q2_alt = q2 * (q1 * ux);
    std::cout << "ux " << ux << " after rotation q2 * (q1 * ux): " << ux_after_q1_q2_alt << " CF: " << ux_after_q1_q2_truth << std::endl;
    if ((ux_after_q1_q2_alt - ux_after_q1_q2_truth).abs().max() > std::numeric_limits<F>::epsilon()) {
        std::cout << "Fail 4 q1_q2_alt\n";
        --rtn;
    }

    // Fails as expected
    sm::vec<F> ux_after_q1q2 = q1q2 * ux;
    if ((ux_after_q1q2 - ux_after_q1_q2_truth).abs().max() > std::numeric_limits<F>::epsilon()) {
        std::cout << "q1q2 fails as expected\n";
    } else {
        std::cout << "Fail 7. q1q2 is expected to fail by didn't\n";
        --rtn;
    }

    sm::vec<F> ux_after_q2q1 = q2q1 * ux;
    std::cout << "ux " << ux << " after combined q2q1 = q2*q1; q2q1 * ux: " << ux_after_q2q1 << " CF: " << ux_after_q1_q2_truth << std::endl;
    if ((ux_after_q2q1 - ux_after_q1_q2_truth).abs().max() > std::numeric_limits<F>::epsilon()) {
        std::cout << "Fail 6 q2q1\n";
        --rtn;
    }
    sm::vec<F> ux_after_q1premultq2 = q1premultq2 * ux;
    if ((ux_after_q1premultq2 - ux_after_q1_q2_truth).abs().max() > std::numeric_limits<F>::epsilon()) {
        std::cout << "Fail 7 q1premultq2\n";
        --rtn;
    }

    // Fails as expected
    sm::vec<F> ux_after_q1postmultq2 = q1postmultq2 * ux;
    if ((ux_after_q1postmultq2 - ux_after_q1_q2_truth).abs().max() > std::numeric_limits<F>::epsilon()) {
        std::cout << "q1postmultq2 expected\n";
    } else {
        std::cout << "Fail 8. q1postmultq2 expected to fail but didn't\n";
        --rtn;
    }


    if (rtn == 0) {
        std::cout << "Rotations tests PASSED\n";
    } else {
        std::cout << "Rotations tests FAILED\n";
    }

    return rtn;
}
