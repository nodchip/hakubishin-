#include <filesystem>
#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "csa.hpp"
#include "thread.hpp"

using namespace std;
using namespace std::tr2::sys;

static const path TEMP_OUTPUT_DIRECTORY_PATH = "../temp";

class CsaTest : public testing::Test {
public:
  CsaTest() {}
  virtual ~CsaTest() {}
protected:
  virtual void SetUp() {
    remove_all(TEMP_OUTPUT_DIRECTORY_PATH);
    create_directories(TEMP_OUTPUT_DIRECTORY_PATH);
  }
  virtual void TearDown() {
    remove_all(TEMP_OUTPUT_DIRECTORY_PATH);
  }
private:
};

TEST_F(CsaTest, toPositions_convertCsaFileToPositions) {
  path filepath = "../src/testdata/csa/wdoor+floodgate-600-10+01WishBlue_07+Apery_i5-4670+20150415003002.csa";

  vector<string> sfen;
  EXPECT_TRUE(csa::toSfen(filepath, sfen));

  EXPECT_EQ(136, sfen.size());
}

TEST_F(CsaTest, toPositions_convertShogidokoroCsaFileToPositions) {
  path filepath = "../src/testdata/shogidokoro/csa/20150823_214751 tanuki- sse4.2 msvc  vs Apery sse4.2 msvc .csa";

  vector<string> sfen;
  EXPECT_TRUE(csa::toSfen(filepath, sfen));

  EXPECT_EQ(134, sfen.size());
}

TEST_F(CsaTest, isFinished_returnTrueIfFinished) {
  path filepath = "../src/testdata/shogidokoro/csa/20150823_214751 tanuki- sse4.2 msvc  vs Apery sse4.2 msvc .csa";

  EXPECT_TRUE(csa::isFinished(filepath));
}

TEST_F(CsaTest, isFinished_returnFalseIfNotFinished) {
  path filepath = "../src/testdata/shogidokoro/csa/not_finished.csa";

  EXPECT_FALSE(csa::isFinished(filepath));
}

TEST_F(CsaTest, isTanukiBlack_returnTrueIfTanikiIsBlack) {
  path filepath = "../src/testdata/shogidokoro/csa/20150823_214751 tanuki- sse4.2 msvc  vs Apery sse4.2 msvc .csa";

  EXPECT_TRUE(csa::isTanukiBlack(filepath));
}

TEST_F(CsaTest, isTanukiBlack_returnFalseIfTanikiIsWhite) {
  path filepath = "../src/testdata/shogidokoro/csa/20150823_215301 Apery sse4.2 msvc  vs tanuki- sse4.2 msvc .csa";

  EXPECT_FALSE(csa::isTanukiBlack(filepath));
}

TEST_F(CsaTest, isBlackWin_returnTrueIfBlackIsWin) {
  path filepath = "../src/testdata/shogidokoro/csa/20150823_215301 Apery sse4.2 msvc  vs tanuki- sse4.2 msvc .csa";

  EXPECT_EQ(Black, csa::getWinner(filepath));
}

TEST_F(CsaTest, isBlackWin_returnTrueIfWhiteIsWin) {
  path filepath = "../src/testdata/shogidokoro/csa/20150823_214751 tanuki- sse4.2 msvc  vs Apery sse4.2 msvc .csa";

  EXPECT_EQ(White, csa::getWinner(filepath));
}

TEST_F(CsaTest, convertCsaToSfen_convertCsaToSfen) {
  path inputDirectoryPath = "../src/testdata/csa";
  path outputFilePath = TEMP_OUTPUT_DIRECTORY_PATH / "temp.sfen";

  EXPECT_TRUE(csa::convertCsaToSfen(
    inputDirectoryPath,
    outputFilePath));

  ifstream ifs(outputFilePath);
  EXPECT_TRUE(ifs.is_open());
  string line;
  EXPECT_TRUE(getline(ifs, line));
  EXPECT_FALSE(getline(ifs, line));
}

TEST_F(CsaTest, convertCsa1LineToSfen_convert) {
  path inputFilePath = "../src/testdata/csa1line/utf82chkifu.csa";
  path outputFilePath = TEMP_OUTPUT_DIRECTORY_PATH / "temp.sfen";

  EXPECT_TRUE(csa::convertCsa1LineToSfen(
    inputFilePath,
    outputFilePath));

  ifstream ifs(outputFilePath);
  EXPECT_TRUE(ifs.is_open());
  string line;
  EXPECT_TRUE(getline(ifs, line));
  EXPECT_TRUE(getline(ifs, line));
  EXPECT_TRUE(getline(ifs, line));
  EXPECT_FALSE(getline(ifs, line));
}
