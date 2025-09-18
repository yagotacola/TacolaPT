#include <iostream>
#include "CLI.h"
#include <chrono>
#include <ctime>
#include <ratio>

#include "smwsock.h"
#include "SrcServer\onserver.h"
#include "netplay.h"
#include "smPacket.h"
#include"GM\GM.h"



using namespace std;
using std::chrono::system_clock;

CLI commandLine;

CLI::CLI()
{
	done = nullptr;
}

CLI::~CLI()
{
}

bool CLI::run(bool* done)
{
	this->done = done;

	std::string input;

	system_clock::time_point today = system_clock::now();

	std::time_t tt = system_clock::to_time_t(today);

	cout << "The Server is ready to go ;)" << endl;
	cout << "Today is: " << ctime(&tt) << endl;
	cout << "Version: 1.0.0.0 - " << "PT" << "!" << endl;
	cout << "Developer: By Staff " << endl << endl;
	cout << "Type: 'help;' to see examples. Type 'exit;' to quit the server." << endl << endl << endl << endl;


	cout << "Server IP	: " << szDefaultServIP << endl;
	cout << "Server Port	: " << TCP_SERVPORT << endl;
	cout << "Server Name	: Priston "  << endl << endl << endl;

	while (!(*this->done))
	{
		cout << "server> ";
		cin >> input;

		if (input.back() != ';')
		{
			cout << "Commands ends with ;" << endl;
		}
		else
		{
			process(input);
		}
	}


	return true;
}

bool CLI::process(const std::string& cmd)
{

	if (cmd.compare("help;") == 0)
		handleHelpCommand();
	else if (cmd.compare("exit;") == 0)
		handleExitCommand();
	else if (cmd.compare("shutdown;") == 0)
		handleShutdownCommand();
	else if (cmd.compare("clear;") == 0)
		system("cls");
	else if (cmd.compare("connected;") == 0)
		handleConnectedCommand();
	else if (cmd.compare(0, 4, "kick") == 0)
		handleKickCommand(cmd);
	else if (cmd.compare("reloadGMS;") == 0)
		handleReloadGMSCommand();
	else if (cmd.compare("showGMS;") == 0)
		handlePrintGMSCommand();
	else if (cmd.compare("reloadConfig;") == 0)
		handleReloadConfigCommand();
	else
		cout << "Invalid command. To see examples, type 'help;'" << endl;
	return false;
}

void CLI::handleHelpCommand()
{
	cout << "Commands ends with ;" << endl;
	cout << "Command: exit; <Close the world>" << endl;
	cout << "Command: shutdown; <Close the world in 8 minutes>" << endl;
	cout << "Command: clear; <Clear CLI screen>" << endl;
	cout << "Command: connected; <Shows who's connected to the world>" << endl;
	cout << "Command: kick(player name); <Expel user from the world>" << endl;
	cout << "Command: reloadGMS; <Reload Game Masters from Database>" << endl;
	cout << "Command: showGMS; <Show active Game Masters.>" << endl;
	cout << "Command: reloadConfig; <Reload the server settings>" << endl;
}

void CLI::handleExitCommand()
{
	*this->done = true;
}

void CLI::handleShutdownCommand()
{
	rsShutDown();
	cout << "The world will be closed in 8 minutes" << endl;
}

void CLI::handleConnectedCommand()
{
	int count = 0;

	for (int cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if (rsPlayInfo[cnt].lpsmSock)
		{
			rsPLAYINFO& player = rsPlayInfo[cnt];

			if (player.lpsmSock)
			{
				cout << "Id: " << player.szID << " - Name: " << player.szName << " - IP: " << player.lpsmSock->szIPAddr << " - Stage: " << player.Position.Area << endl;
				count++;
			}
		}
	}

	if (count) cout << "Connected users: " << count << endl;
}

void CLI::handleKickCommand(const std::string& cmd)
{
	if (cmd.length() < 6)
		return;

	std::string name;
	bool flag = false;

	for (auto it = cmd.begin() + 5; it != cmd.end(); ++it)
	{
		if (*it == ')')
		{
			flag = true;
			break;
		}

		name += *it;

	}

	if (!flag) return;

	rsPLAYINFO* player = FindUserFromName(const_cast<char*>(name.c_str()));

	if (!player)
	{
		player = FindUserFromName2(const_cast<char*>(name.c_str()));
	}

	if (player)
	{
		DisconnectUser(player->lpsmSock);
	}
}

void CLI::handlePrintGMSCommand()
{
	GameMasters::getInstance()->print();
}

void CLI::handleReloadGMSCommand()
{
	GameMasters::getInstance()->readFromDatabase();
	cout << "GMS reloaded" << endl;
}

void CLI::handleReloadConfigCommand()
{
	int rsRefreshConfig();

	rsRefreshConfig();
	

	cout << "Settings reloaded" << endl;
}

CLI* CLI::getInstance()
{
	return &commandLine;
}
