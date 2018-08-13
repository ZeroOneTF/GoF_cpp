#include <cstring>
#include <stdexcept>

#include <corona10/buffered_reader.hpp>

constexpr int DEFAULT_BUFFER_SIZE = 8192;

namespace corona10 {

Reader::~Reader() {}

FileReader::FileReader(const char *fname) {
  this->fd = fopen(fname, "rb");
  if (this->fd == nullptr) {
    throw std::runtime_error("Can not open a file");
  }
}

FileReader::~FileReader() {
  if (this->fd) {
    fclose(this->fd);
  }
}

int FileReader::read(char *buf, int offset, int count) {
  std::fseek(this->fd, offset, SEEK_SET);
  return std::fread(buf, sizeof(char), count, this->fd);
}

ReaderDecorator::ReaderDecorator(Reader *reader) : p_reader(reader) {}

ReaderDecorator::~ReaderDecorator() { delete this->p_reader; }

int ReaderDecorator::read(char *buf, int offset, int count) {
  return this->p_reader->read(buf, offset, count);
}

BufferedReader::BufferedReader(Reader *reader)
    : ReaderDecorator(reader), pos(0), limit(0), markPos(-1) {
  this->buffer = new char[DEFAULT_BUFFER_SIZE];
  memset(this->buffer, 0, DEFAULT_BUFFER_SIZE);
}

BufferedReader::~BufferedReader() { delete[] this->buffer; }

int BufferedReader::read(char *buf, int offset, int count) {
  int avail = this->limit - this->pos;
  if (count > avail) {

    if (avail > 0) {
      count = avail;
    } else {
      bool isEndOfBuffer = false;
      if (this->limit == DEFAULT_BUFFER_SIZE) {
        this->markPos = -1;
      }
      if (pos > limit) {
        isEndOfBuffer = true;
        --this->pos;
      }

      if (this->markPos < 0) {

        if (count >= DEFAULT_BUFFER_SIZE && !isEndOfBuffer) {
          // Direct read
          return ReaderDecorator::read(buf, offset, count);
        }

        this->pos = 0;
        this->limit = 0;
      }
      avail = ReaderDecorator::read(this->buffer, limit,
                                    DEFAULT_BUFFER_SIZE - limit);
      if (isEndOfBuffer && avail > 0 && this->buffer[this->limit] == '\n') {
        avail--;
        this->limit++;
      }

      if (avail < count) {
        if (avail <= 0)
          return avail;
        count = avail;
      }
      this->limit += avail;
    }
  }

  std::memcpy(&buf[offset], &this->buffer[pos], count);
  this->pos += count;
  return count;
}
} // namespace corona10