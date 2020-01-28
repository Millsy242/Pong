//
//  PongSaveStruct.hpp
//  Pong
//
//  Created by Daniel Harvey on 28/01/2020.
//  Copyright © 2020 Daniel Harvey. All rights reserved.
//

#ifndef PongSaveStruct_hpp
#define PongSaveStruct_hpp

struct PongSaveStruct
{
public:
    float P1PosX,P1PosY,P1VelX,P1VelY,P1SizeX,P1SizeY;
    float P2PosX,P2PosY,P2VelX,P2VelY,P2SizeX,P2SizeY;
    float BPosX,BPosY,BVelX,BVelY,BSizeX,BSizeY;
    int P1Score,P2Score,BLastTouched;
    int SaveID;
};

#endif /* PongSaveStruct_hpp */
