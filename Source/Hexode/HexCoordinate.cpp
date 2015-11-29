// hexode.xyz

#include "Hexode.h"
#include "HexCoordinate.h"

FHexCoordinate::FHexCoordinate()
{
	this->U = 0;
	this->V = 0;
}

FHexCoordinate::FHexCoordinate(int32 CoordU, int32 CoordV)
{
	this->U = CoordU;
	this->V = CoordV;
}
