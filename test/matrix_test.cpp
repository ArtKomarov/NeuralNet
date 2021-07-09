#include "gtest/gtest.h"

#include "matrix.h"

struct MatrixTest : public ::testing::Test {
    Matrix* m_;
    virtual void SetUp() override {
        m_ = new Matrix();
    }

    virtual void TearDown() override {
        delete m_;
    }
};

// Constructor tests
TEST(MatrixTests, ConstructorTest1) {
    std::vector<matrix_t> a = {1.1, 2.2, 3.3};

    Matrix m(a);

    ASSERT_EQ(m[0][0], 1.1);
    ASSERT_EQ(m[0][1], 2.2);
    ASSERT_EQ(m[0][2], 3.3);
}

// Summary tests
TEST(MatrixTests, SumTest1) {
    Matrix m1(3, 7, 1);
    Matrix m2(3, 7, 8);

    Matrix sum = m1 + m2;

    Matrix true_sum(3, 7, 9);

    ASSERT_EQ(sum, true_sum);
}

TEST(MatrixTests, SumTest2) {
    Matrix m1(3, 7, 3);

    Matrix sum = m1 + 5;

    Matrix true_sum(3, 7, 8);

    ASSERT_EQ(sum, true_sum);
}

TEST(MatrixTests, SumTest3) {
    Matrix m1(3, 7, 3);

    Matrix sum = 5 + m1;

    Matrix true_sum(3, 7, 8);

    ASSERT_EQ(sum, true_sum);
}

// Subtraction tests
TEST(MatrixTests, SubTest1) {
    Matrix m1(7, 22, 1.1);
    Matrix m2(7, 22, 8.3);

    Matrix sub = m1 - m2;

    Matrix true_sub(7, 22, 1.1 - 8.3);

    ASSERT_EQ(sub, true_sub);
}

// Multiplication tests
TEST(MatrixTests, MulTest1) {
    Matrix m1(2, 3, 1);
    Matrix m2(3, 5, 1);

    Matrix mul = m1 * m2;

    Matrix true_mul(2, 5, 3);

    ASSERT_EQ(mul, true_mul);
}

TEST(MatrixTests, MulTest2) {
    Matrix m1(10, 1, 3);
    Matrix m2(1, 50, 5);

    Matrix mul = m1 * m2;

    Matrix true_mul(10, 50, 15);

    ASSERT_EQ(mul, true_mul);
}

TEST(MatrixTests, MulTest3) {
    Matrix m1(1, 5, 2);
    Matrix m2(5, 2, 3);

    Matrix mul = m1 * m2;

    Matrix true_mul(1, 2, 30);

    ASSERT_EQ(mul, true_mul);
}

TEST(MatrixTests, MulTest4) {
    Matrix m1(2, 4, 2.2);
    Matrix m2(4, 5, 3.3);
    Matrix m3(5, 3, 4.4);

    Matrix mul = m1 * m2 * m3;

    Matrix true_mul(2, 3, 2.2 * 3.3 * 4 * 4.4 * 5);

    ASSERT_EQ(mul, true_mul) << "Sizes: "  << mul.getRows()      << " x " << mul.getColumns()
                             << ", true: " << true_mul.getRows() << " x " << true_mul.getColumns() << std::endl;
}

// sum func test
TEST(MatrixTests, SumFuncTest1) {
    Matrix m(2, 3);
    m.fillRandom();

    matrix_t sum = 0;

    for (size_t i = 0; i < m.getRows(); i++) {
        for (size_t j = 0; j < m.getColumns(); j++) {
            sum += m[i][j];
        }
    }

    ASSERT_EQ(m.sum(), sum);
}
