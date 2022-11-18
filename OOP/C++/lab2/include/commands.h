#ifndef LAB2_COMMANDS_H
#define LAB2_COMMANDS_H
#include <iostream>
#include <map>
#include <chrono>
#include "life.h"

class ICommand {
public:
	virtual int execute(Field& field, Galaxy& galaxy, std::vector<std::string> words) = 0;
};

class Exit : public ICommand {
public:
	int execute(Field& field, Galaxy& galaxy, std::vector<std::string> words) override;
};

class Help : public ICommand {
public:
	int execute(Field& field, Galaxy& galaxy, std::vector<std::string> words) override;
};

class Tick : public ICommand {
public:
	int execute(Field& field, Galaxy& galaxy, std::vector<std::string> words) override;
};

class Play : public ICommand {
public:
	int execute(Field& field, Galaxy& galaxy, std::vector<std::string> words) override;
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

std::vector<std::string> split(const std::string& line, char dev);
std::map<std::string, ICommand*> createCommandList();


#endif
