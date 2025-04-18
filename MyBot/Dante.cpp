﻿#include "Dante.h"
#include <dpp/unicode_emoji.h>
#include <time.h>
#include <dpp/dpp.h>

static void dante() {
	std::cout << "===================================================================================== \n";
	std::cout << "===================================================================================== \n\n";
	std::cout << " ______          _        ____  _____   _________   ________     _   _   _\n";
	std::cout << "|_   _ `.       / \\      |_   \\|_   _| |  _   _  | |_   __  |   | | | | | |\n";
	std::cout << "  | | `. \\     / _ \\       |   \\ | |   |_/ | | \\_|   | |_ \\_|   | | | | | |\n";
	std::cout << "  | |  | |    / ___ \\      | |\\ \\| |       | |       |  _| _    | | | | | |\n";
	std::cout << " _| |_.' /  _/ /   \\ \\_   _| |_\\   |_     _| |_     _| |__/ |   |_| |_| |_|\n";
	std::cout << "|______.'  |____| |____| |_____|\\____|   |_____|   |________|   (_) (_) (_)\n\n\n";
	std::cout << "===================================================================================== \n";
	std::cout << "===================================================================================== \n\n";
}

int main() {
	dante();
	srand(time(NULL));

	dpp::cluster bot(" ", dpp::i_default_intents | dpp::i_message_content);

	bot.on_log(dpp::utility::cout_logger());

	/*============================EMOJI REACTIONS============================*/
	bot.on_message_create([&bot](const dpp::message_create_t& event) {
		if (dpp::lowercase(event.msg.content).find("pizza") != std::string::npos) {
			bot.message_add_reaction(event.msg.id, event.msg.channel_id, dpp::unicode_emoji::pizza);
		}
		});

	/*============================MESSAGE LISTENERS============================*/
	bot.on_message_create([&bot](const dpp::message_create_t& event) {

		if (event.msg.author.is_bot() || event.msg.content.empty()) {
			return;
		}
		//JUST DANTE
		else if (dpp::lowercase(event.msg.content).find("dante") != std::string::npos) {
			if (dpp::lowercase(event.msg.content).find("dante") != std::string::npos && dpp::lowercase(event.msg.content).find("edit") != std::string::npos) {
				event.reply("[⠀](https://cdn.discordapp.com/attachments/1226821071655800902/1285098939812675606/ssstik.io_presclouds_1726460271751.mp4?ex=66e90927&is=66e7b7a7&hm=4273ab52e232402f38d69b985f603b06c8d42486327f12fc345a1459ff8b5b0d&)", true);
			}
			else if (dpp::lowercase(event.msg.content).find("foolishness") != std::string::npos && dpp::lowercase(event.msg.content).find("dante") != std::string::npos) {
				event.reply("## <:foolishness:1289569573384884365>: foolishness, " + event.msg.author.username + ", foolishness.", true);
			}
			else if (dpp::lowercase(event.msg.content).find("hi") != std::string::npos) {
				if (event.msg.author.username == "fluorescentmay") {
					event.reply("Hi May!!!", true);
				}
				else {
					event.reply("Hi " + event.msg.author.username + "!", true);
				}
			}
			else {
				event.reply("Hey there! Looking for me? <:Dante_heart:1310501782442610698><:dante_stylish:1347543360771985448>", true);

			}
		}
		//MENTIONS
		else if (dpp::lowercase(event.msg.content).find("<@1282558635502731334>") != std::string::npos) {
			int randReply = rand() % 5;
			std::string replies[5] = {
				"Hi",
				"<a:dantepapitadantedmc3:1325330088685731933>",
				"Let\'s get the party started!!",
				"<:dante_stylish:1347543360771985448> looking for me?",
				"https://tenor.com/view/dante-dmc3-devil-may-cry-3-hakari-dance-dante-hakari-dance-gif-7597429884320385687"
			};
			event.reply(replies[randReply], true);
			}
		});

	/*============================SLASH COMMANDS============================*/
	//Clear Commands
	bot.on_ready([&bot](const dpp::ready_t& event) {
		if (dpp::run_once<struct clear_bot_commands>()) {
			bot.global_bulk_command_delete();
		}
		});

	//Commands
	bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
		if (event.command.get_command_name() == "command") {
			dpp::embed embed = dpp::embed()
				.set_color(dpp::colors::maroon)
				.set_title("Dante Commands!!")
				.set_description("list of keywords")
				.set_thumbnail("https://cdn.discordapp.com/attachments/1226821071655800902/1284825020023181438/dante_at_your_door.jpg?ex=66e80a0b&is=66e6b88b&hm=a8c498a43e0eaaf561fc37512c0e07542a885c907f97f10b54c23c6def4dfe7e&")
				.add_field(
					"MAIN KEYWORDS",
					"Dante\nHi Dante\nDante Edit"
				)
				.add_field(
					"EMOJI REACTIONS",
					"Pizza",
					true
				)
				.set_footer(
					dpp::embed_footer()
					.set_text("Dry ahh bot")
					.set_icon("https://cdn.discordapp.com/attachments/1226821071655800902/1285124475481755753/601f354a8cdd104c003e8b9ebf2c4e76.png?ex=66e920ef&is=66e7cf6f&hm=bfffcb418daf9d40036fd71e797b3fef3f4b1f47add1ab5c082edf78a0a13278&")
				)
				.set_timestamp(time(0));


			dpp::message msg(event.command.channel_id, embed);


			event.reply(msg);
		}
		});
	//Register Commands
	bot.on_ready([&bot](const dpp::ready_t& event) {
		bot.set_presence(dpp::presence(dpp::ps_dnd, dpp::at_custom, "Devil's never cry"));
		if (dpp::run_once<struct register_bot_commands>()) {
			dpp::slashcommand commandscommand("command", "List of keywords", bot.me.id);

			bot.global_bulk_command_create({ commandscommand });
		}
		});

	bot.start(dpp::st_wait);

	return 0;
}