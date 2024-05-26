use alloc::vec::Vec;
use group::{ff::Field, GroupEncoding};
use num_bigint::BigInt;
use num_traits::Zero;
use rand::thread_rng;

use crate::scalar_mul::VartimeMultiscalarMul;

use super::NonAdjacentForm;

/// Generates test vectors for [`test_jubjub_vartime_multiscalar_mul`].
// #[test]
#[allow(dead_code)]
fn gen_jubjub_test_vectors() {
    use group::Group;
    use std::println;

    let rng = thread_rng();

    let scalars = [
        jubjub::Scalar::random(rng.clone()),
        jubjub::Scalar::random(rng.clone()),
    ];
    println!("Scalars:");
    for scalar in scalars {
        println!("{:?}", scalar.to_bytes());
    }

    let points = [
        jubjub::ExtendedPoint::random(rng.clone()),
        jubjub::ExtendedPoint::random(rng),
    ];
    println!("Points:");
    for point in points {
        println!("{:?}", point.to_bytes());
    }

    let res = jubjub::ExtendedPoint::vartime_multiscalar_mul(scalars, points);
    println!("Result:");
    println!("{:?}", res.to_bytes());
}

/// Checks if the vartime multiscalar multiplication on Jubjub produces the expected product.
/// The test vectors were generated by [`gen_jubjub_test_vectors`].
#[test]
fn test_jubjub_vartime_multiscalar_mul() {
    let scalars: [[u8; 32]; 2] = [
        [
            147, 209, 135, 83, 133, 175, 29, 28, 22, 161, 0, 220, 100, 218, 103, 47, 134, 242, 49,
            19, 254, 204, 107, 185, 189, 155, 33, 110, 100, 141, 59, 0,
        ],
        [
            138, 136, 196, 249, 144, 2, 9, 103, 233, 93, 253, 46, 181, 12, 41, 158, 62, 201, 35,
            198, 108, 139, 136, 78, 210, 12, 1, 223, 231, 22, 92, 13,
        ],
    ];

    let points: [[u8; 32]; 2] = [
        [
            93, 252, 67, 45, 63, 170, 103, 247, 53, 37, 164, 250, 32, 210, 38, 71, 162, 68, 205,
            176, 116, 46, 209, 66, 131, 209, 107, 193, 210, 153, 222, 31,
        ],
        [
            139, 112, 204, 231, 187, 141, 159, 122, 210, 164, 7, 162, 185, 171, 47, 199, 5, 33, 80,
            207, 129, 24, 165, 90, 204, 253, 38, 27, 55, 86, 225, 52,
        ],
    ];

    let expected_product: [u8; 32] = [
        64, 228, 212, 168, 76, 90, 248, 218, 86, 22, 182, 130, 227, 52, 170, 88, 220, 193, 166,
        131, 180, 48, 148, 72, 212, 148, 212, 240, 77, 244, 91, 213,
    ];

    let scalars: Vec<jubjub::Scalar> = scalars
        .into_iter()
        .map(|s| jubjub::Scalar::from_bytes(&s).expect("Could not deserialize a `jubjub::Scalar`."))
        .collect();

    let points: Vec<jubjub::ExtendedPoint> = points
        .into_iter()
        .map(|p| {
            jubjub::ExtendedPoint::from_bytes(&p)
                .expect("Could not deserialize a `jubjub::ExtendedPoint`.")
        })
        .collect();

    let expected_product = jubjub::ExtendedPoint::from_bytes(&expected_product)
        .expect("Could not deserialize a `jubjub::ExtendedPoint`.");

    let product = jubjub::ExtendedPoint::vartime_multiscalar_mul(scalars, points);
    assert_eq!(expected_product, product);
}

/// Tests the non-adjacent form for a Jubjub scalar.
#[test]
fn test_non_adjacent_form() {
    let rng = thread_rng();

    let scalar = jubjub::Scalar::random(rng);
    test_non_adjacent_form_for_scalar(5, scalar);
}

/// Tests the non-adjacent form for a particular scalar.
pub(crate) fn test_non_adjacent_form_for_scalar<Scalar: NonAdjacentForm>(w: usize, scalar: Scalar) {
    let naf = scalar.non_adjacent_form(w);
    let naf_length = Scalar::naf_length();

    // Check that the computed w-NAF has the intended length.
    assert_eq!(naf.len(), naf_length);

    let w = u32::try_from(w).expect("The window `w` did not fit into `u32`.");

    // `bound` <- 2^(w-1)
    let bound = 2_i32.pow(w - 1);

    // `valid_coeffs` <- a range of odd integers from -2^(w-1) to 2^(w-1)
    let valid_coeffs: Vec<i32> = (-bound..bound).filter(|x| x.rem_euclid(2) == 1).collect();

    let mut reconstructed_scalar: BigInt = Zero::zero();

    // Reconstruct the original scalar, and check two general invariants for any w-NAF along the
    // way.
    let mut i = 0;
    while i < naf_length {
        if naf[i] != 0 {
            // In a w-NAF, every nonzero coefficient `naf[i]` is an odd signed integer with
            // -2^(w-1) < `naf[i]` < 2^(w-1).
            assert!(valid_coeffs.contains(&i32::from(naf[i])));

            // Incrementally keep reconstructing the original scalar.
            reconstructed_scalar += naf[i] * BigInt::from(2).pow(i.try_into().unwrap());

            // In a w-NAF, at most one of any `w` consecutive coefficients is nonzero.
            for _ in 1..w {
                i += 1;
                if i >= naf_length {
                    break;
                }
                assert_eq!(naf[i], 0)
            }
        }

        i += 1;
    }

    // Check that the reconstructed scalar is not negative, and convert it to little-endian bytes.
    let reconstructed_scalar = reconstructed_scalar
        .to_biguint()
        .expect("The reconstructed scalar is negative.")
        .to_bytes_le();

    // Check that the reconstructed scalar is not too big.
    assert!(reconstructed_scalar.len() <= 32);

    // Convert the reconstructed scalar to a fixed byte array so we can compare it with the orginal
    // scalar.
    let mut reconstructed_scalar_bytes: [u8; 32] = [0; 32];
    for (i, byte) in reconstructed_scalar.iter().enumerate() {
        reconstructed_scalar_bytes[i] = *byte;
    }

    // Check that the reconstructed scalar matches the original one.
    assert_eq!(reconstructed_scalar_bytes, scalar.inner_to_bytes());
}
