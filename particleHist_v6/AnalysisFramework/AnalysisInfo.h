#ifndef AnalysisInfo_h
#define AnalysisInfo_h

#include <string>
#include <vector>

class AnalysisInfo {

 public:

  enum AnalysisStatus { begin, end };

  AnalysisInfo( int argc, char* argv[] );
  // deleted copy constructor and assignment to prevent unadvertent copy
  AnalysisInfo           ( const AnalysisInfo& x ) = delete;
  AnalysisInfo& operator=( const AnalysisInfo& x ) = delete;

  ~AnalysisInfo();

  // get the list of all words
  const std::vector<std::string>& argList() const;
  // get the word coming after the word 'key'
  const std::string& value( const std::string& key ) const;
  // check if the word 'key' is present
  bool contains( const std::string& key ) const;
  // set new value for a 'key'
  void setValue(std::string key, std::string value) const;
 private:

  // container for words
  mutable std::vector<std::string> args;
  // value to return for keys not found
  static std::string defaultString;

};

#endif

