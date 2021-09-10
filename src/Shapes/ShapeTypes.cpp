#include "Shapes/ShapeTypes.hpp"

std::string ShapeTypesUtils::GetShapeTypeName(ShapeTypes Type) {
	switch (Type) {
	case ShapeTypes::ST_Sphere:
		return "Sphere";

	default:
		return "";
	}
}
