// hexode.xyz

#include "Hexode.h"
#include "HexCoordinate.h"
#include <math.h>

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

int32 UHexUtil::Amplitude(FHexCoordinate Vector)
{
	int32 U = Vector.U;
	int32 V = Vector.V;
	return (abs(U)
		+ abs(U + V)
		+ abs(V)) / 2;
}

float UHexUtil::Angle(FHexCoordinate Vector1, FHexCoordinate Vector2)
{
	float X1 = sqrt(3) * (Vector1.U + Vector1.V / 2.0);
	float Y1 = 1.5 * Vector1.V;
	float X2 = sqrt(3) * (Vector2.U + Vector2.V / 2.0);
	float Y2 = 1.5 * Vector2.V;

	float Dot = X1 * X2 + Y1 * Y2;
	float Det = X1 * Y2 - Y1 * X2;

	return atan2(Det, Dot);
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