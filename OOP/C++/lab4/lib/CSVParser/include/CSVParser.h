#pragma once
#include <fstream>
#include <string>
#include <tuple>
#include <sstream>
#include "CSVParserExceptionis.h"

enum IteratorMode {
	BEGIN,
	END
};

template <typename... Types>
class CSVParser {
public:
	CSVParser(std::ifstream& file, int numLinesForSkip) 
		: inputFile(file), numLinesForSkip(numLinesForSkip) {
		if (!inputFile.is_open()) throw std::ios_base::failure("file is not opened");
	}

	std::string getRow() {
		std::string row;
		if (!std::getline(inputFile, row)) throw std::ios_base::failure("file was already red");
		else {
			++currentLine;
			return row;
		}
	}

	std::vector<std::string> getCells(const std::string& line) {
		std::vector<std::string> args;
		std::stringstream stream;
		stream.str(line);
		std::string item;
		while (std::getline(stream, item, rowDelim)) {
			args.push_back(item);
		}
		return args;
	}

	int getNumOfLine() {
		return currentLine;
	}

	class Iterator;

	Iterator begin() {
		Iterator it(*this, BEGIN);
		skipLines(it);
		return it;
	}

	Iterator end() {
		Iterator it(*this, END);
		return it;
	}

private:
	void skipLines(Iterator& it) {
		for (int i = 0; i < numLinesForSkip; ++i) {
			++it;
		}
	}

	std::ifstream& inputFile;
	int numLinesForSkip;
	int currentLine = 0;
	char columnDelim = '\n';
	char rowDelim = ';';
};

template <typename...Types>
class CSVParser<Types...>::Iterator {
public:
	using value_type = std::tuple<Types...>;
	using reference = std::tuple<Types...>&;
	using pointer = std::unique_ptr<std::tuple<Types...>>;

	Iterator() = default;
	Iterator(CSVParser<Types...>& parser, IteratorMode mode) : parser(parser) {
		if (mode == BEGIN) updatePointer();
		if (mode == END) ptr = nullptr;
	}

	bool operator!=(const Iterator& other) {
		return this->ptr != other.ptr;
	}

	bool operator==(const Iterator& other) {
		return this->ptr == other.ptr;
	}

	Iterator& operator++() {
		try {
			updatePointer();
			return *this;
		}
		catch (IncorrectTypeOfCell& ex) {
			throw;
		}
	}

	value_type operator*() {
		return tupleValue;
	}

private:
	value_type tupleValue;
	pointer ptr;
	CSVParser<Types...>& parser;

	template <typename T>
	bool isTypeCorrect(T value, std::string cell) {
		std::ostringstream os;
		os << value;
		if (os.str() == cell) return true;
		else return false;
	}

	void readTuple(std::vector<std::string>& cells, int curPos, int_<sizeof...(Types)>) {}

	template<size_t Size>
	void readTuple(std::vector<std::string>& cells, int curPos, int_<Size>) {
		std::tuple_element_t<Size, std::tuple<Types...>> value;
		std::istringstream(cells[Size]) >> value;
		if (!isTypeCorrect(value, cells[Size])) throw IncorrectTypeOfCell(parser.getNumOfLine(), Size + 1);
		std::get<Size>(tupleValue) = value;
		readTuple(cells, curPos + 1, int_<Size + 1>());
	}

	void updatePointer() {
		try {
			std::string line = parser.getRow();
			std::vector<std::string> cells = parser.getCells(line);
			readTuple(cells, 0, int_<0>());
			ptr = std::make_unique<std::tuple<Types...>>(tupleValue);
		}
		catch (IncorrectTypeOfCell& ex) {
			throw;
		}
		catch (std::exception& ex) {
			ptr = nullptr;
		}
	}
};
