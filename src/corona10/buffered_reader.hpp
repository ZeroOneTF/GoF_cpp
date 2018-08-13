#ifndef _BUFFERED_READER_HPP
#define _BUFFERED_READER_HPP
#include <string>

namespace corona10 {

class Reader {
public:
  virtual ~Reader() = 0;
  virtual int read(char *buf, int offset, int count) = 0;
};

class ReaderDecorator : public Reader {
public:
  explicit ReaderDecorator(Reader *reader);
  ~ReaderDecorator();
  int read(char *buf, int offset, int count) override;

private:
  Reader *p_reader;
};

class FileReader : public Reader {
public:
  explicit FileReader(const char *fname);
  ~FileReader();
  int read(char *buf, int offset, int count) override;

private:
  FILE *fd;
};

class BufferedReader : public ReaderDecorator {
public:
  explicit BufferedReader(Reader *reader);
  ~BufferedReader();
  int read(char *buf, int offset, int count) override;

private:
  int pos;
  int limit;
  int markPos;
  char *buffer;
};
} // namespace corona10

#endif