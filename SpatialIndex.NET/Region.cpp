#include "stdafx.h"
#include "Region.h"
#include "SpatialIndexException.h"

using namespace Konscious::SpatialIndex;
using namespace System;

Region::Region(cli::array<double> ^min, cli::array<double> ^max)
{
	if (min->Length != max->Length)
	{
		throw gcnew ArgumentException("Min and max points have different dimensions", "max");
	}

	pin_ptr<double> low = &min[0];
	pin_ptr<double> high = &max[0];

	_region = new ::SpatialIndex::Region(low, high, min->Length);
}

Region::Region(Point ^min, Point ^max)
{
	_region = new ::SpatialIndex::Region(*min->_point, *max->_point);
}

Region::~Region()
{
	delete _region;
}


Point ^Region::Minimum::get()
{
	auto copyFrom = new ::SpatialIndex::Point(_region->m_pLow, _region->m_dimension);
	return gcnew Point(copyFrom);
}

Point ^Region::Maximum::get()
{
	auto copyFrom = new ::SpatialIndex::Point(_region->m_pHigh, _region->m_dimension);
	return gcnew Point(copyFrom);
}

Region ^Region::BoundingRegion::get()
{
	return this;
}

Region::Region(::SpatialIndex::Region *region) 
	: _region(region)
{
}

::SpatialIndex::IShape *Region::getShape()
{
	return _region;
}

unsigned int Region::dimensions()
{
	return _region->getDimension();
}
