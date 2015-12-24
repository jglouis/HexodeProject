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


int32 UHexUtil::Distance(FHexCoordinate Coord1, FHexCoordinate Coord2)
{
	int32 U1 = Coord1.U;
	int32 V1 = Coord1.V;
	int32 U2 = Coord2.U;
	int32 V2 = Coord2.V;
	return (abs(U1 - U2)
		+ abs(U1 + V1 - U2 - V2)
		+ abs(V1 - V2)) / 2;
}

FHexCoordinate UHexUtil::Addition(FHexCoordinate Coord1, FHexCoordinate Coord2)
{
	Coord1.U += Coord2.U;
	Coord1.V += Coord2.V;
	return Coord1;
}

FHexCoordinate UHexUtil::Substraction(FHexCoordinate Coord1, FHexCoordinate Coord2)
{
	Coord1.U -= Coord2.U;
	Coord1.V -= Coord2.V;
	return Coord1;
}