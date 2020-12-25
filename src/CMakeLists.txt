include_directories(.)

add_executable(
  range-setup

  range-setup.cpp
)
target_link_libraries(
  range-setup

  snark
)
target_include_directories(
  range-setup

  PUBLIC
  ${DEPENDS_DIR}/libsnark
  ${DEPENDS_DIR}/libsnark/depends/libfqfft
)

add_executable(
  range-prove

  range-prove.cpp
)
target_link_libraries(
  range-prove

  snark
)
target_include_directories(
  range-prove

  PUBLIC
  ${DEPENDS_DIR}/libsnark
  ${DEPENDS_DIR}/libsnark/depends/libfqfft
)

add_executable(
  range-verify

  range-verify.cpp
)
target_link_libraries(
  range-verify

  snark
)
target_include_directories(
  range-verify

  PUBLIC
  ${DEPENDS_DIR}/libsnark
  ${DEPENDS_DIR}/libsnark/depends/libfqfft
)