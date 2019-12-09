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
 *  @file    spawnCollect.cpp
 *  @author  Prasheel Renkuntla
 *  @author  Raj Shinde
 *  @date    12/09/2019
 *  @version 3.0
 *  @brief   Final Project - ecobot (A trash Collecting Robot)
 *  @section Implemention of spawn and collect methods.
 */

#include <spawnCollect.hpp>
#include <cstdlib>
#include <string>

SpawnCollect::SpawnCollect() {
}

SpawnCollect::~SpawnCollect() {
}

bool SpawnCollect::spawn(int xr, int yr, int flag) {
// String to spawn construction cone in gazebo world
std::string spawn11 ="rosrun gazebo_ros spawn_model -database construction_cone -sdf -model cab1 -z 0.0 -y ";
std::string spawn2 = " -x ";
std::string spawna = spawn11 + std::to_string(yr) + spawn2 +
                     std::to_string(xr);
if(flag == 1) {
// Enter in terminal
system(spawna.c_str());
}
return true;
}
bool SpawnCollect::collect(int flag) {
if(flag == 1) {
// Delete construction cone from gazebo world
system("rosservice call gazebo/delete_model '{model_name: cab1}'");
}
return true;
}
