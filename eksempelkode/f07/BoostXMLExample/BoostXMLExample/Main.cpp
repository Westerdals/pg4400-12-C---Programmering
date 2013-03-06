/**
 * @file: Main.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <06.03.2013>
 * 
 * @description: A program testing Boost's property tree library
 *				 to read and fetch values from a XML file.
 */

// Standard includes
#include <iostream>
#include <string>

// Boost property tree includes
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>
#include <boost\property_tree\exceptions.hpp>

// A couple of usings to make life easier
using namespace boost::property_tree;
using std::cout;
using std::cerr;
using std::endl;

// The entire program is written in main
int main(int argc, char* argv[])
{
	try
	{
		// Load XML file
		ptree config;
		xml_parser::read_xml("config.xml", config);

		// Get Window properties, default width & height: 550x400 - default occurs if it fails
		int winWidth = config.get("app.gfx.resolution.width", 550);
		int winHeight = config.get("app.gfx.resolution.height", 400);
		std::string name = config.get<std::string>("app.name");

		// Print window properties
		cout << name << endl << winWidth << "x" << winHeight << endl << endl;
		
		// Fetch sprites, iterate and print sprite names
		ptree sprites = config.get_child("app.sprites");

		for (auto it = sprites.begin(); it != sprites.end(); ++it) {
			cout << it->second.get<std::string>("filename") << endl;
		}

		system("pause");
		return EXIT_SUCCESS;
	}
	catch (const ptree_error& e) // File doesn't exist, file permission errors, ivalid XML etc.
	{
		cerr << "An error occured, details: " << e.what() << endl;
	}
	catch (...)
	{
		cerr << "An unknown error occured" << endl;
	}
	
	system("pause");
	return EXIT_FAILURE;
}