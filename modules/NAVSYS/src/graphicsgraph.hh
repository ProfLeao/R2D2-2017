/**
* \file      graphicsgraph.hh
* \brief     header for graphes in sfmlgraphics window
* \author    Leo Jenneskens
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/
#pragma once 
#include <vector>
#include "graphicsvertices.hh" 
#include "graphicsnodes.hh" 
#include "graph.hh" 
#include "node.hh"

#include <SFML/Graphics.hpp>


class graphicalfactory {
private:	
	Graph * g;
	std::vector<graphnodes> graphicalnodes;
	std::vector<vertices>graphicalvertices;
	
public:
	/**
	*constructor of the grahicalfactory.
	*
	*in this constructor will a stored graph set in objects ready to print on an sfml window
	*
	*
	**/
	graphicalfactory(Graph * g );
	/**
	*draw function for graph
	*
	*This function will draw the nodes en vertices in the windwo given in the parameter.
	*/
	

	void draw(sf::RenderWindow & window);
	

	



	






};


