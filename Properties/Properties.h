/*
  Properties.h - Event-Based Library for Arduino.
  Copyright (c) 2011, Renato A. Ferreira
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
      * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
      * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
      * Neither the name of the <organization> nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef Properties_h
#define Properties_h

#include <stdlib.h>
#include <avr/eeprom.h>
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define DEFAULT_POSITION 0
#define MAX_VARIABLES 30

struct PropertyInformation {
	short propertyId;
	short valueSize;
	void* value;
};

class PropertiesClass
{
  public:
  	short count;
	short size;
    PropertiesClass();
	bool load();
	bool load(short position);
	void save();
	void save(short position);
	void flush();
	void set(short propertyId, int value);
	void set(short propertyId, long value);
	void set(short propertyId, void* data, short dataSize);
	int getInt(short propertyId);
	long getLong(short propertyId);
	PropertyInformation* get(short propertyId);
	
  private:
	short mallocSize;
	short index;
    short mainPosition;
	short lastInt;
	short lastLong;
	PropertyInformation* moveProperty;
    PropertyInformation* properties;
	PropertyInformation* currentProperty;
	void remove(short propertyId);
	void addProperty(short propertyId, short dataSize);
	void setPosition(short position);
	bool findProperty(short propertyId);
	void fixPointers();
	void readEEPROM(short position, byte* data, short size);
	void writeEEPROM(short position, byte* data, short size);
};

//global instance
extern PropertiesClass Properties;

#endif