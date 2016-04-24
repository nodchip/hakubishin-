﻿#ifndef APERY_USI_HPP
#define APERY_USI_HPP

#include "common.hpp"
#include "move.hpp"
#include "tt.hpp"

namespace USI
{

  constexpr const char* DefaultStartPositionSFEN = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL b - 1";

  struct OptionsMap;

  namespace OptionNames
  {
    constexpr const char* USI_HASH = "USI_Hash";
    constexpr const char* CLEAR_HASH = "Clear_Hash";
    constexpr const char* BOOK_FILE = "Book_File";
    constexpr const char* BEST_BOOK_MOVE = "Best_Book_Move";
    constexpr const char* OWNBOOK = "OwnBook";
    constexpr const char* MIN_BOOK_PLY = "Min_Book_Ply";
    constexpr const char* MAX_BOOK_PLY = "Max_Book_Ply";
    constexpr const char* MIN_BOOK_SCORE = "Min_Book_Score";
    constexpr const char* EVAL_DIR = "Eval_Dir";
    constexpr const char* WRITE_SYNTHESIZED_EVAL = "Write_Synthesized_Eval";
    constexpr const char* USI_PONDER = "USI_Ponder";
    constexpr const char* BYOYOMI_MARGIN = "Byoyomi_Margin";
    constexpr const char* MULTIPV = "MultiPV";
    constexpr const char* MAX_RANDOM_SCORE_DIFF = "Max_Random_Score_Diff";
    constexpr const char* MAX_RANDOM_SCORE_DIFF_PLY = "Max_Random_Score_Diff_Ply";
    constexpr const char* SLOW_MOVER = "Slow_Mover";
    constexpr const char* MINIMUM_THINKING_TIME = "Minimum_Thinking_Time";
    constexpr const char* THREADS = "Threads";
    constexpr const char* DANGER_DEMERIT_SCORE = "Danger_Demerit_Score";
    constexpr const char* OUTPUT_INFO = "Output_Info";
    constexpr const char* SEARCH_WINDOW_OFFSET = "Search_Window_Offset";
    constexpr const char* MOVE_OVERHEAD = "Move_Overhead";
    constexpr const char* NODESTIME = "nodestime";
  }

  class USIOption {
    using Fn = void(const USIOption&);
  public:
    USIOption(Fn* = nullptr);
    USIOption(const char* v, Fn* = nullptr);
    USIOption(const bool v, Fn* = nullptr);
    USIOption(const int v, const int min, const int max, Fn* = nullptr);

    USIOption& operator = (const std::string& v);

    operator int() const {
      assert(type_ == "check" || type_ == "spin");
      return (type_ == "spin" ? atoi(currentValue_.c_str()) : currentValue_ == "true");
    }

    operator std::string() const {
      assert(type_ == "string");
      return currentValue_;
    }

    const std::string& type() const { return type_; }
    const std::string& defaultValue() const { return defaultValue_; }
    int min() const { return min_; }
    int max() const { return max_; }

  private:
    std::string defaultValue_;
    std::string currentValue_;
    std::string type_;
    int min_;
    int max_;
    Fn* onChange_;
  };

  struct CaseInsensitiveLess {
    bool operator() (const std::string&, const std::string&) const;
  };

  struct OptionsMap : public std::map<std::string, USIOption, CaseInsensitiveLess> {
  private:
    static const USIOption INVALID_OPTION;
  public:
    void init();
    bool isLegalOption(const std::string name) {
      return this->find(name) != std::end(*this);
    }
    const USIOption& operator[] (const std::string& name) const {
      const auto it = this->find(name);
      if (it != this->end()) {
        return it->second;
      }
      return INVALID_OPTION;
    }
    USIOption& operator[] (const std::string& name) {
      return std::map<std::string, USIOption, CaseInsensitiveLess>::operator[](name);
    }
  };

  void go(const Position& pos, const std::string& cmd);
  void go(const Position& pos, std::istringstream& ssCmd);
  void setPosition(Position& pos, const std::string& cmd);
  void setPosition(Position& pos, std::istringstream& ssCmd);
  void setOption(const std::string& cmd);
  void setOption(std::istringstream& ssCmd);
#if defined LEARN
  void go(const Position& pos, const Ply depth, const Move move);
#endif
  Move csaToMove(const Position& pos, const std::string& moveStr);
  Move usiToMove(const Position& pos, const std::string& moveStr);
  std::string score(Score sore, Score alpha, Score beta);
  std::string score(Score score);
  std::string pv(const Position& pos, Depth depth, Score alpha, Score beta);
  void doUSICommandLoop(int argc, char* argv[]);
}

extern USI::OptionsMap Options;

#endif // #ifndef APERY_USI_HPP
