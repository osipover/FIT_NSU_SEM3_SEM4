#pragma once
#include "life.h"
#include <memory>

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
};

class Play : public ICommand {
public:
	int execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) override;
};

class Dump : public ICommand {
public:
	int execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) override;
};

class ICommandCreator {
public:
	virtual std::unique_ptr<ICommand> create() = 0;
};

class ExitCreator : public ICommandCreator {
	std::unique_ptr<ICommand> create() override {
		auto ptr = std::unique_ptr<ICommand>{ new Exit };
		return ptr;
	}
};

class HelpCreator : public ICommandCreator{
	std::unique_ptr<ICommand> create() override {
		auto ptr = std::unique_ptr<ICommand>{ new Help };
		return ptr;
	}
};

class TickCreator : public ICommandCreator {
	std::unique_ptr<ICommand> create() override {
		auto ptr = std::unique_ptr<ICommand>{ new Tick };
		return ptr;
	}
};

class PlayCreator : public ICommandCreator {
	std::unique_ptr<ICommand> create() override {
		auto ptr = std::unique_ptr<ICommand>{ new Play };
		return ptr;
	}
};

class DumpCreator : public ICommandCreator {
	std::unique_ptr<ICommand> create() override {
		auto ptr = std::unique_ptr<ICommand>{ new Dump };
		return ptr;
	}
};

std::vector<std::string> split(const std::string& line, char dev);
std::map<std::string, std::unique_ptr<ICommand>> createCommandList();

class CommandExceptions : public std::exception {
public:
	CommandExceptions(const char* msg) :std::exception(msg) {}
private:
};

