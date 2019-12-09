/************************************************************************
BSD 3-Clause License

Copyright (c) 2019, Raj Shinde
Copyright (c) 2019, Prasheel Renkuntla
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *************************************************************************/

/**
 *  @copyright BSD 3-Clause License 
 *  @copyright Copyright © 2019 Raj Shinde, Prasheel Renkuntla
 *  @file    randomizer.hpp
 *  @author  Prasheel Renkuntla
 *  @author  Raj Shinde
 *  @date    12/09/2019
 *  @version 3.0
 *  @brief   Final Project - ecobot (A trash Collecting Robot)
 *  @section Header file for randomizing trash.
 */

#ifndef INCLUDE_RANDOMIZER_HPP_
#define INCLUDE_RANDOMIZER_HPP_

class Randomizer {
public:
	double xc, yc;

  /**
   *   @brief Constructor of class Randomizer
   *   @param none
   *   @return none
   */
	Randomizer();

  /**
   *   @brief Destructor of class Randomizer
   *   @param none
   *   @return none
   */
	~Randomizer();

  /**
   *   @brief function to randomize x
   *   @param none
   *   @return double xr
   */
	double randomizeX();

  /**
   *   @brief function to randomize y
   *   @param none
   *   @return double yr
   */
	double randomizeY();

  /**
   *   @brief function to offset x
   *   @param double xo, robot origin
   *   @param double xr, trash
   *   @param double xn, target
   *   @return double xn, new traget
   */
	double xOffset(double xo, double xr, double xn);

  /**
   *   @brief function to offset y
   *   @param double yo, robot origin
   *   @param double yr, trash
   *   @param double yn, traget
   *   @return double yn, new target
   */
	double yOffset(double yo, double yr, double yn);
};

#endif  //  INCLUDE_RANDOMIZER_HPP_