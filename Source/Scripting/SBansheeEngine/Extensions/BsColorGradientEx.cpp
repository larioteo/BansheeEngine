//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "BsColorGradientEx.h"

namespace bs
{
	Color ColorGradientEx::evaluate(const SPtr<ColorGradient>& thisPtr, float t)
	{
		Color output;
		output.setAsRGBA(thisPtr->evaluate(t));

		return output;
	}
}
