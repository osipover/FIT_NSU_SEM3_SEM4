#pragma once
#include "life.h"

class ICommand {
public:
	virtual int execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) = 0;
};

class Exit : public ICommand {
public:
	int execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) override;
};

class Help : public ICommand {
public:
	int execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) override;
};

class Tick : public ICommand {
public:
	int execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) override;
private:
	void outputField(Field& field);
};

class Play : public ICommand {
public:
	int execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) override;
private:
	void outputField(Field& field);
};

class Dump : public ICommand {
public:
	int execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) override;
private:
	void outputField(std::ofstream&,Field&);
};

class ICommandCreator {
public: 
	virtual ICommand* create() = 0;
};

class ExitCreator : public ICommandCreator {
	ICommand* create() override {
		return new Exit;
	}
};

class HelpCreator : public ICommandCreator{
	ICommand* create() override {
		return new Help;
	}
};

class TickCreator : public ICommandCreator {
	ICommand* create() override {
		return new Tick;
	}
};

class PlayCreator : public ICommandCreator {
	ICommand* create() override {
		return new Play;
	}
};

class DumpCreator : public ICommandCreator {
	ICommand* create() override {
		return new Dump;
	}
};

class CommandExceptions : public std::exception {
public:
	CommandExceptions(const char* msg) :std::exception(msg) {}
private:
};
