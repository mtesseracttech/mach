//
// Created by mtesseract on 7/3/19.
//

#ifndef MACH_PROPERTIES_HPP
#define MACH_PROPERTIES_HPP

namespace mach {
	#define PROPERTY(_type, _name, _get, _put) __declspec(property(get=_get, put=_put)) _type _name
	#define PROPERTY_READONLY(_type, _name, _get) __declspec(property(get=_get)) _type _name
	#define PROPERTY_WRITEONLY(_type, _name, _set) __declspec(property(put=_put)) _type _name
}

#endif //MACH_PROPERTIES_HPP
