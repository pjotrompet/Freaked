/* ------------------------------------------------------------
Code generated with Faust 2.0.a40 (http://faust.grame.fr)
------------------------------------------------------------ */

#ifndef  __Prefreak_H__
#define  __Prefreak_H__
/************************************************************************
 ************************************************************************
    FAUST Architecture File
    Copyright (C) 2009-2011 Albert Graef <Dr.Graef@t-online.de>
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation; either version 2.1 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with the GNU C Library; if not, write to the Free
    Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA.
 ************************************************************************
 ************************************************************************/

/* LV2 architecture for Faust. */

#include <stdlib.h>
#include <math.h>
#include <list>
#include <map>

using namespace std;

// On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
// flags to avoid costly denormals
#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
  #define AVOIDDENORMALS
#endif

typedef pair<const char*,const char*> strpair;

struct Meta
{
  list< strpair > data;
  void declare (const char* key, const char* value)
  { data.push_back(strpair(key, value)); }
};

//-------------------------------------------------------------------
// Generic min and max using c++ inline
//-------------------------------------------------------------------

inline int 	max (unsigned int a, unsigned int b) { return (a>b) ? a : b; }
inline int 	max (int a, int b)		{ return (a>b) ? a : b; }

inline long 	max (long a, long b) 		{ return (a>b) ? a : b; }
inline long 	max (int a, long b) 		{ return (a>b) ? a : b; }
inline long 	max (long a, int b) 		{ return (a>b) ? a : b; }

inline float 	max (float a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (int a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (float a, int b) 		{ return (a>b) ? a : b; }
inline float 	max (long a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (float a, long b) 		{ return (a>b) ? a : b; }

inline double 	max (double a, double b) 	{ return (a>b) ? a : b; }
inline double 	max (int a, double b) 		{ return (a>b) ? a : b; }
inline double 	max (double a, int b) 		{ return (a>b) ? a : b; }
inline double 	max (long a, double b) 		{ return (a>b) ? a : b; }
inline double 	max (double a, long b) 		{ return (a>b) ? a : b; }
inline double 	max (float a, double b) 	{ return (a>b) ? a : b; }
inline double 	max (double a, float b) 	{ return (a>b) ? a : b; }


inline int	min (int a, int b)		{ return (a<b) ? a : b; }

inline long 	min (long a, long b) 		{ return (a<b) ? a : b; }
inline long 	min (int a, long b) 		{ return (a<b) ? a : b; }
inline long 	min (long a, int b) 		{ return (a<b) ? a : b; }

inline float 	min (float a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (int a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (float a, int b) 		{ return (a<b) ? a : b; }
inline float 	min (long a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (float a, long b) 		{ return (a<b) ? a : b; }

inline double 	min (double a, double b) 	{ return (a<b) ? a : b; }
inline double 	min (int a, double b) 		{ return (a<b) ? a : b; }
inline double 	min (double a, int b) 		{ return (a<b) ? a : b; }
inline double 	min (long a, double b) 		{ return (a<b) ? a : b; }
inline double 	min (double a, long b) 		{ return (a<b) ? a : b; }
inline double 	min (float a, double b) 	{ return (a<b) ? a : b; }
inline double 	min (double a, float b) 	{ return (a<b) ? a : b; }

// abs is now predefined
//template<typename T> T abs (T a)		{ return (a<T(0)) ? -a : a; }

inline int	lsr (int x, int n)		{ return int(((unsigned int)x) >> n); }

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }


/******************************************************************************
*******************************************************************************

			ABSTRACT USER INTERFACE

*******************************************************************************
*******************************************************************************/

class UI
{
  bool	fStopped;
public:

  UI() : fStopped(false) {}
  virtual ~UI() {}

  virtual void addButton(const char* label, float* zone) = 0;
  virtual void addCheckButton(const char* label, float* zone) = 0;
  virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
  virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
  virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;

  virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
  virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;

  virtual void openTabBox(const char* label) = 0;
  virtual void openHorizontalBox(const char* label) = 0;
  virtual void openVerticalBox(const char* label) = 0;
  virtual void closeBox() = 0;

  virtual void run() = 0;

  void stop() { fStopped = true; }
  bool stopped() { return fStopped; }

  virtual void declare(float* zone, const char* key, const char* value) {}
};

/***************************************************************************
   LV2 UI interface
 ***************************************************************************/

enum ui_elem_type_t {
  UI_BUTTON, UI_CHECK_BUTTON,
  UI_V_SLIDER, UI_H_SLIDER, UI_NUM_ENTRY,
  UI_V_BARGRAPH, UI_H_BARGRAPH,
  UI_END_GROUP, UI_V_GROUP, UI_H_GROUP, UI_T_GROUP
};

struct ui_elem_t {
  ui_elem_type_t type;
  const char *label;
  int port;
  float *zone;
  void *ref;
  float init, min, max, step;
};

class LV2UI : public UI
{
public:
  int nelems, nports;
  ui_elem_t *elems;
  map< int, list<strpair> > metadata;

  LV2UI();
  virtual ~LV2UI();

protected:
  void add_elem(ui_elem_type_t type, const char *label = NULL);
  void add_elem(ui_elem_type_t type, const char *label, float *zone);
  void add_elem(ui_elem_type_t type, const char *label, float *zone,
		float init, float min, float max, float step);
  void add_elem(ui_elem_type_t type, const char *label, float *zone,
		float min, float max);

public:
  virtual void addButton(const char* label, float* zone);
  virtual void addCheckButton(const char* label, float* zone);
  virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step);
  virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step);
  virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);

  virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max);
  virtual void addVerticalBargraph(const char* label, float* zone, float min, float max);

  virtual void openTabBox(const char* label);
  virtual void openHorizontalBox(const char* label);
  virtual void openVerticalBox(const char* label);
  virtual void closeBox();

  virtual void run();

  virtual void declare(float* zone, const char* key, const char* value);
};

LV2UI::LV2UI()
{
  nelems = nports = 0;
  elems = NULL;
}

LV2UI::~LV2UI()
{
  if (elems) free(elems);
}

void LV2UI::declare(float* zone, const char* key, const char* value)
{
  map< int, list<strpair> >::iterator it = metadata.find(nelems);
  if (it != metadata.end())
    it->second.push_back(strpair(key, value));
  else
    metadata[nelems] = list<strpair>(1, strpair(key, value));
}

inline void LV2UI::add_elem(ui_elem_type_t type, const char *label)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  elems[nelems].type = type;
  elems[nelems].label = label;
  elems[nelems].port = -1;
  elems[nelems].zone = NULL;
  elems[nelems].ref = NULL;
  elems[nelems].init = 0.0;
  elems[nelems].min = 0.0;
  elems[nelems].max = 0.0;
  elems[nelems].step = 0.0;
  nelems++;
}

inline void LV2UI::add_elem(ui_elem_type_t type, const char *label, float *zone)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  elems[nelems].type = type;
  elems[nelems].label = label;
  elems[nelems].port = nports++;
  elems[nelems].zone = zone;
  elems[nelems].ref = NULL;
  elems[nelems].init = 0.0;
  elems[nelems].min = 0.0;
  elems[nelems].max = 0.0;
  elems[nelems].step = 0.0;
  nelems++;
}

inline void LV2UI::add_elem(ui_elem_type_t type, const char *label, float *zone,
			     float init, float min, float max, float step)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  elems[nelems].type = type;
  elems[nelems].label = label;
  elems[nelems].port = nports++;
  elems[nelems].zone = zone;
  elems[nelems].ref = NULL;
  elems[nelems].init = init;
  elems[nelems].min = min;
  elems[nelems].max = max;
  elems[nelems].step = step;
  nelems++;
}

inline void LV2UI::add_elem(ui_elem_type_t type, const char *label, float *zone,
			     float min, float max)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  elems[nelems].type = type;
  elems[nelems].label = label;
  elems[nelems].port = nports++;
  elems[nelems].zone = zone;
  elems[nelems].ref = NULL;
  elems[nelems].init = 0.0;
  elems[nelems].min = min;
  elems[nelems].max = max;
  elems[nelems].step = 0.0;
  nelems++;
}

void LV2UI::addButton(const char* label, float* zone)
{ add_elem(UI_BUTTON, label, zone); }
void LV2UI::addCheckButton(const char* label, float* zone)
{ add_elem(UI_CHECK_BUTTON, label, zone); }
void LV2UI::addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_V_SLIDER, label, zone, init, min, max, step); }
void LV2UI::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_H_SLIDER, label, zone, init, min, max, step); }
void LV2UI::addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_NUM_ENTRY, label, zone, init, min, max, step); }

void LV2UI::addHorizontalBargraph(const char* label, float* zone, float min, float max)
{ add_elem(UI_H_BARGRAPH, label, zone, min, max); }
void LV2UI::addVerticalBargraph(const char* label, float* zone, float min, float max)
{ add_elem(UI_V_BARGRAPH, label, zone, min, max); }

void LV2UI::openTabBox(const char* label)
{ add_elem(UI_T_GROUP, label); }
void LV2UI::openHorizontalBox(const char* label)
{ add_elem(UI_H_GROUP, label); }
void LV2UI::openVerticalBox(const char* label)
{ add_elem(UI_V_GROUP, label); }
void LV2UI::closeBox()
{ add_elem(UI_END_GROUP); }

void LV2UI::run() {}

/******************************************************************************
*******************************************************************************

			    FAUST DSP

*******************************************************************************
*******************************************************************************/

//----------------------------------------------------------------
//  abstract definition of a signal processor
//----------------------------------------------------------------

class dsp {
 protected:
  int fSamplingFreq;
 public:
  // internal freelist for custom voice allocation
  dsp *prev, *next;
  dsp() {}
  virtual ~dsp() {}
  virtual int getNumInputs() = 0;
  virtual int getNumOutputs() = 0;
  virtual void buildUserInterface(UI* interface) = 0;
  virtual void init(int samplingRate) = 0;
  virtual void compute(int len, float** inputs, float** outputs) = 0;
};

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif



#ifndef FAUSTCLASS
#define FAUSTCLASS Prefreak
#endif

class Prefreak : public dsp {

  public:

	float fVec17[262144];
	float fVec18[262144];
	float fVec19[262144];
	float fVec20[262144];
	float fVec15[131072];
	float fVec16[131072];
	float fVec13[65536];
	float fVec14[65536];
	float fVec11[32768];
	float fVec12[32768];
	float fVec10[16384];
	float fVec9[8192];
	float fVec8[4096];
	float fVec7[2048];
	float fVec5[512];
	float fVec6[512];
	float fVec4[128];
	float fVec1[64];
	float fVec0[2];
	float fVec2[2];
	float fVec3[2];
	FAUSTFLOAT fHslider0;
	int IOTA;
	FAUSTFLOAT fHslider1;
	int fSamplingFreq;

  public:

	void static metadata(Meta* m) {
		m->declare("compilation_options", "-single -vec -vs 128 -mcd 64");
		m->declare("library_path", "PreFreak");
	}

	virtual int getNumInputs() {
		return 2;

	}
	virtual int getNumOutputs() {
		return 2;

	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}

		}
		return rate;

	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}

		}
		return rate;

	}

	static void classInit(int samplingFreq) {

	}

	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fHslider0 = FAUSTFLOAT(1.);
		for (int i0 = 0; (i0 < 2); i0 = (i0 + 1)) {
			fVec0[i0] = 0.f;

		}
		IOTA = 0;
		for (int i1 = 0; (i1 < 64); i1 = (i1 + 1)) {
			fVec1[i1] = 0.f;

		}
		fHslider1 = FAUSTFLOAT(0.6);
		for (int i2 = 0; (i2 < 2); i2 = (i2 + 1)) {
			fVec2[i2] = 0.f;

		}
		for (int i3 = 0; (i3 < 2); i3 = (i3 + 1)) {
			fVec3[i3] = 0.f;

		}
		for (int i4 = 0; (i4 < 128); i4 = (i4 + 1)) {
			fVec4[i4] = 0.f;

		}
		for (int i5 = 0; (i5 < 512); i5 = (i5 + 1)) {
			fVec5[i5] = 0.f;

		}
		for (int i6 = 0; (i6 < 512); i6 = (i6 + 1)) {
			fVec6[i6] = 0.f;

		}
		for (int i7 = 0; (i7 < 2048); i7 = (i7 + 1)) {
			fVec7[i7] = 0.f;

		}
		for (int i8 = 0; (i8 < 4096); i8 = (i8 + 1)) {
			fVec8[i8] = 0.f;

		}
		for (int i9 = 0; (i9 < 8192); i9 = (i9 + 1)) {
			fVec9[i9] = 0.f;

		}
		for (int i10 = 0; (i10 < 16384); i10 = (i10 + 1)) {
			fVec10[i10] = 0.f;

		}
		for (int i11 = 0; (i11 < 32768); i11 = (i11 + 1)) {
			fVec11[i11] = 0.f;

		}
		for (int i12 = 0; (i12 < 32768); i12 = (i12 + 1)) {
			fVec12[i12] = 0.f;

		}
		for (int i13 = 0; (i13 < 65536); i13 = (i13 + 1)) {
			fVec13[i13] = 0.f;

		}
		for (int i14 = 0; (i14 < 65536); i14 = (i14 + 1)) {
			fVec14[i14] = 0.f;

		}
		for (int i15 = 0; (i15 < 131072); i15 = (i15 + 1)) {
			fVec15[i15] = 0.f;

		}
		for (int i16 = 0; (i16 < 131072); i16 = (i16 + 1)) {
			fVec16[i16] = 0.f;

		}
		for (int i17 = 0; (i17 < 262144); i17 = (i17 + 1)) {
			fVec17[i17] = 0.f;

		}
		for (int i18 = 0; (i18 < 262144); i18 = (i18 + 1)) {
			fVec18[i18] = 0.f;

		}
		for (int i19 = 0; (i19 < 262144); i19 = (i19 + 1)) {
			fVec19[i19] = 0.f;

		}
		for (int i20 = 0; (i20 < 262144); i20 = (i20 + 1)) {
			fVec20[i20] = 0.f;

		}

	}

	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}

	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("0x00");
		interface->addHorizontalSlider("Pre-DelTime's", &fHslider1, 0.6f, 0.f, 15.f, 0.1f);
		interface->addHorizontalSlider("PreGain", &fHslider0, 1.f, 1.f, 999.f, 0.5f);
		interface->closeBox();

	}

	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (1.f / (0.f - (min(999.f, max(0.f, float(fHslider0))) - 1000.f)));
		float fSlow1 = min(30.f, max(0.f, float(fHslider1)));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			float fTemp1 = float(input1[i]);
			fVec0[0] = (fTemp0 - fTemp1);
			fVec1[(IOTA & 63)] = (0.f - ((fTemp0 + fTemp1) - fVec0[1]));
			fVec2[0] = fSlow1;
			fVec3[0] = (fSlow1 + fVec2[1]);
			float fTemp2 = ((fVec3[1] + fVec2[1]) + fSlow1);
			fVec4[(IOTA & 127)] = (0.f - (((fVec0[1] + fTemp0) + fTemp1) - fVec1[((IOTA - max(1, int(fTemp2))) & 63)]));
			float fTemp3 = (fVec0[1] + fVec1[((IOTA - max(1, int(fTemp2))) & 63)]);
			float fTemp4 = (fVec4[((IOTA - max(1, int((2.f * fTemp2)))) & 127)] + fTemp3);
			fVec5[(IOTA & 511)] = (0.f - (((fTemp3 + fTemp0) + fTemp1) - fVec4[((IOTA - max(1, int((2.f * fTemp2)))) & 127)]));
			fVec6[(IOTA & 511)] = (0.f - (((fTemp4 + fTemp0) + fTemp1) - fVec5[((IOTA - max(1, int((5.f * fTemp2)))) & 511)]));
			float fTemp5 = (fVec5[((IOTA - max(1, int((5.f * fTemp2)))) & 511)] + fTemp4);
			float fTemp6 = (fVec6[((IOTA - max(1, int((7.f * fTemp2)))) & 511)] + fTemp5);
			fVec7[(IOTA & 2047)] = (0.f - (((fTemp5 + fTemp0) + fTemp1) - fVec6[((IOTA - max(1, int((7.f * fTemp2)))) & 511)]));
			fVec8[(IOTA & 4095)] = (0.f - (((fTemp6 + fTemp0) + fTemp1) - fVec7[((IOTA - max(1, int((23.f * fTemp2)))) & 2047)]));
			float fTemp7 = (fVec7[((IOTA - max(1, int((23.f * fTemp2)))) & 2047)] + fTemp6);
			float fTemp8 = (fVec8[((IOTA - max(1, int((54.f * fTemp2)))) & 4095)] + fTemp7);
			fVec9[(IOTA & 8191)] = (0.f - (((fTemp7 + fTemp0) + fTemp1) - fVec8[((IOTA - max(1, int((54.f * fTemp2)))) & 4095)]));
			fVec10[(IOTA & 16383)] = (0.f - (((fTemp8 + fTemp0) + fTemp1) - fVec9[((IOTA - max(1, int((79.f * fTemp2)))) & 8191)]));
			float fTemp9 = (fVec9[((IOTA - max(1, int((79.f * fTemp2)))) & 8191)] + fTemp8);
			float fTemp10 = (fVec10[((IOTA - max(1, int((220.f * fTemp2)))) & 16383)] + fTemp9);
			fVec11[(IOTA & 32767)] = (0.f - (((fTemp9 + fTemp0) + fTemp1) - fVec10[((IOTA - max(1, int((220.f * fTemp2)))) & 16383)]));
			fVec12[(IOTA & 32767)] = (0.f - (((fTemp10 + fTemp0) + fTemp1) - fVec11[((IOTA - max(1, int((340.f * fTemp2)))) & 32767)]));
			float fTemp11 = (fVec11[((IOTA - max(1, int((340.f * fTemp2)))) & 32767)] + fTemp10);
			float fTemp12 = (fVec12[((IOTA - max(1, int((454.f * fTemp2)))) & 32767)] + fTemp11);
			fVec13[(IOTA & 65535)] = (0.f - (((fTemp11 + fTemp0) + fTemp1) - fVec12[((IOTA - max(1, int((454.f * fTemp2)))) & 32767)]));
			fVec14[(IOTA & 65535)] = (0.f - (((fTemp12 + fTemp0) + fTemp1) - fVec13[((IOTA - max(1, int((623.f * fTemp2)))) & 65535)]));
			float fTemp13 = (fVec13[((IOTA - max(1, int((623.f * fTemp2)))) & 65535)] + fTemp12);
			float fTemp14 = (fVec14[((IOTA - max(1, int((845.f * fTemp2)))) & 65535)] + fTemp13);
			fVec15[(IOTA & 131071)] = (0.f - (((fTemp13 + fTemp0) + fTemp1) - fVec14[((IOTA - max(1, int((845.f * fTemp2)))) & 65535)]));
			fVec16[(IOTA & 131071)] = (0.f - (((fTemp14 + fTemp0) + fTemp1) - fVec15[((IOTA - max(1, int((1304.f * fTemp2)))) & 131071)]));
			float fTemp15 = (fVec15[((IOTA - max(1, int((1304.f * fTemp2)))) & 131071)] + fTemp14);
			float fTemp16 = (fVec16[((IOTA - max(1, int((1532.f * fTemp2)))) & 131071)] + fTemp15);
			fVec17[(IOTA & 262143)] = (0.f - (((fTemp15 + fTemp0) + fTemp1) - fVec16[((IOTA - max(1, int((1532.f * fTemp2)))) & 131071)]));
			fVec18[(IOTA & 262143)] = (0.f - (((fTemp16 + fTemp0) + fTemp1) - fVec17[((IOTA - max(1, int((2204.f * fTemp2)))) & 262143)]));
			float fTemp17 = (fVec17[((IOTA - max(1, int((2204.f * fTemp2)))) & 262143)] + fTemp16);
			float fTemp18 = (fVec18[((IOTA - max(1, int((3137.f * fTemp2)))) & 262143)] + fTemp17);
			fVec19[(IOTA & 262143)] = (0.f - (((fTemp17 + fTemp0) + fTemp1) - fVec18[((IOTA - max(1, int((3137.f * fTemp2)))) & 262143)]));
			fVec20[(IOTA & 262143)] = (0.f - (((fTemp18 + fTemp0) + fTemp1) - fVec19[((IOTA - max(1, int((3567.f * fTemp2)))) & 262143)]));
			output0[i] = FAUSTFLOAT(min(1.f, max(-1.f, (fSlow0 * fVec20[((IOTA - max(1, int((4218.f * fTemp2)))) & 262143)]))));
			output1[i] = FAUSTFLOAT(min(1.f, max(-1.f, (fSlow0 * (((fVec19[((IOTA - max(1, int((3567.f * fTemp2)))) & 262143)] + fTemp18) + fTemp0) + fTemp1)))));
			fVec0[1] = fVec0[0];
			IOTA = (IOTA + 1);
			fVec2[1] = fVec2[0];
			fVec3[1] = fVec3[0];

		}

	}


};


#ifdef FAUST_UIMACROS
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0
	FAUST_ADDHORIZONTALSLIDER("Pre-DelTime's", fHslider1, 0.6f, 0.0f, 15.0f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("PreGain", fHslider0, 1.0f, 1.0f, 999.0f, 0.5f);
#endif

//----------------------------------------------------------------------------
//  LV2 interface
//----------------------------------------------------------------------------

//#line 391 "lv2.cpp"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This enables automatic MIDI controller mapping based on the midi:ctrl
   attributes in the Faust source. We have this enabled by default, but you
   may have to disable it if the custom controller mapping gets in the way of
   the automation facilities that the host provides. (But then again if the
   host wants to do its own controller mapping then it probably won't, or at
   least shouldn't, send us the MIDI controllers in the first place.) */
#ifndef FAUST_MIDICC
#define FAUST_MIDICC 1
#endif

#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/ext/dynmanifest/dynmanifest.h>
#if FAUST_MIDICC
#include <lv2/lv2plug.in/ns/ext/atom/util.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#define MIDI_EVENT_URI "http://lv2plug.in/ns/ext/midi#MidiEvent"
#endif

#ifndef URI_PREFIX
#define URI_PREFIX "http://faust-lv2.googlecode.com"
#endif

#ifndef PLUGIN_URI
#define PLUGIN_URI URI_PREFIX "/Prefreak"
#endif

/* This allows various manifest data to be generated from the corresponding
   metadata (author, name, description, license) in the Faust source. */
#ifndef FAUST_META
#define FAUST_META 1
#endif

// You can define these for various debugging output items.
//#define DEBUG_META 1 // recognized MIDI controller metadata
//#define DEBUG_MIDI 1 // incoming MIDI messages
//#define DEBUG_MIDICC 1 // controller messages

struct LV2Plugin {
  bool active;		// activation status
  int rate;		// sampling rate
  Prefreak *dsp;		// the dsp
  LV2UI *ui;		// its Faust interface description
  int n_in, n_out;	// number of input and output control ports
  int *ctrls;		// Faust ui elements (indices into ui->elems)
  float **ports;	// corresponding LV2 data
  float *portvals;	// cached port data from the last run
  int *inctrls, *outctrls;	// indices for active and passive controls
  float **inputs, **outputs;	// audio buffers
#if FAUST_MIDICC
  LV2_Atom_Sequence* event_port; // midi input
  std::map<uint8_t,int> ctrlmap; // MIDI controller map
  // Needed host features.
  LV2_URID_Map* map;	// the urid extension
  LV2_URID midi_event;	// midi event uri
#endif

  LV2Plugin() {
    active = false;
    rate = 44100;
    n_in = n_out = 0;
    dsp = NULL;
    ui = NULL;
    ctrls = inctrls = outctrls = NULL;
    ports = inputs = outputs = NULL;
    portvals = NULL;
#if FAUST_MIDICC
    map = NULL;
    midi_event = -1;
    event_port = NULL;
#endif
  }
};

static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{
  LV2Plugin* plugin = new LV2Plugin;
#if FAUST_MIDICC
  // Scan host features for URID map.
  for (int i = 0; features[i]; i++) {
    if (!strcmp(features[i]->URI, LV2_URID_URI "#map")) {
      plugin->map = (LV2_URID_Map*)features[i]->data;
      plugin->midi_event =
	plugin->map->map(plugin->map->handle, MIDI_EVENT_URI);
    }
  }
  if (!plugin->map) {
    fprintf
      (stderr, "%s: host doesn't support urid:map, giving up\n",
       PLUGIN_URI);
    delete plugin;
    return 0;
  }
#endif
  plugin->rate = rate;
  plugin->dsp = new Prefreak();
  plugin->ui = new LV2UI();
  plugin->dsp->init(plugin->rate);
  plugin->dsp->buildUserInterface(plugin->ui);
  // The LV2 ports are numbered as follows: 0..k-1 are the control ports, then
  // come the n audio input ports, finally the m audio output ports (and
  // possibly a MIDI input port).
  int k = plugin->ui->nports, p = 0, q = 0;
  int n = plugin->dsp->getNumInputs(), m = plugin->dsp->getNumOutputs();
  // Allocate tables for the control elements and their LV2 ports.
  plugin->ctrls = (int*)calloc(k, sizeof(int));
  plugin->inctrls = (int*)calloc(k, sizeof(int));
  plugin->outctrls = (int*)calloc(k, sizeof(int));
  plugin->ports = (float**)calloc(k, sizeof(float*));
  plugin->portvals = (float*)calloc(k, sizeof(float));
  assert(k == 0 || (plugin->ctrls && plugin->inctrls && plugin->outctrls &&
		    plugin->ports && plugin->portvals));
  // Scan the Faust UI for active and passive controls which become the
  // input and output control ports of the LV2 plugin, respectively.
  for (int i = 0, j = 0; i < plugin->ui->nelems; i++) {
    switch (plugin->ui->elems[i].type) {
    case UI_T_GROUP: case UI_H_GROUP: case UI_V_GROUP: case UI_END_GROUP:
      // control groups
      break;
    case UI_H_BARGRAPH: case UI_V_BARGRAPH:
      // passive controls (output ports)
      plugin->ctrls[j++] = i;
      plugin->outctrls[q++] = i;
      break;
    default:
      // active controls (input ports)
#if FAUST_MIDICC
      {
	std::map< int, list<strpair> >::iterator it =
	  plugin->ui->metadata.find(i);
	if (it != plugin->ui->metadata.end()) {
	  // Scan for controller mappings.
	  for (std::list<strpair>::iterator jt = it->second.begin();
	       jt != it->second.end(); jt++) {
	    const char *key = jt->first, *val = jt->second;
#if DEBUG_META
	    fprintf(stderr, "ctrl '%s' meta: '%s' -> '%s'\n",
		    plugin->ui->elems[i].label, key, val);
#endif
	    if (strcmp(key, "midi")) continue;
	    unsigned num;
	    if (sscanf(val, "ctrl %u", &num) < 1) continue;
#if 0 // enable this to get feedback about controller assignments
	    fprintf(stderr, "%s: cc %d -> %s\n", PLUGIN_URI, num,
		    plugin->ui->elems[i].label);
#endif
	    plugin->ctrlmap.insert(std::pair<uint8_t,int>(num, p));
	  }
	}
      }
#endif
      plugin->ctrls[j++] = i;
      plugin->inctrls[p++] = i;
      int p = plugin->ui->elems[i].port;
      float val = plugin->ui->elems[i].init;
      plugin->portvals[p] = val;
      break;
    }
  }
  // Realloc the inctrls and outctrls vectors to their appropriate sizes.
  plugin->inctrls = (int*)realloc(plugin->inctrls, p*sizeof(int));
  assert(p == 0 || plugin->inctrls);
  plugin->outctrls = (int*)realloc(plugin->outctrls, q*sizeof(int));
  assert(q == 0 || plugin->outctrls);
  plugin->n_in = p; plugin->n_out = q;
  // Allocate vectors for the audio input and output ports. Like
  // plugin->ports, these will be initialized in the connect_port callback.
  plugin->inputs = (float**)calloc(n, sizeof(float*));
  assert(n == 0 || plugin->inputs);
  plugin->outputs = (float**)calloc(m, sizeof(float*));
  assert(m == 0 || plugin->outputs);
  return (LV2_Handle)plugin;
}

static void
cleanup(LV2_Handle instance)
{
  LV2Plugin* plugin = (LV2Plugin*)instance;
  delete plugin->dsp;
  delete plugin->ui;
  free(plugin->ctrls);
  free(plugin->inctrls);
  free(plugin->outctrls);
  free(plugin->ports);
  free(plugin->portvals);
  free(plugin->inputs);
  free(plugin->outputs);
  delete plugin;
}

static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
  LV2Plugin* plugin = (LV2Plugin*)instance;
  int i = port, k = plugin->ui->nports;
  int n = plugin->dsp->getNumInputs(), m = plugin->dsp->getNumOutputs();
  if (i < k)
    plugin->ports[i] = (float*)data;
  else {
    i -= k;
    if (i < n)
      plugin->inputs[i] = (float*)data;
    else {
      i -= n;
      if (i < m)
	plugin->outputs[i] = (float*)data;
#if FAUST_MIDICC
      else if (i == m)
	plugin->event_port = (LV2_Atom_Sequence*)data;
#endif
      else
	fprintf(stderr, "%s: bad port number %u\n", PLUGIN_URI, port);
    }
  }
}

#if FAUST_MIDICC
static float ctrlval(const ui_elem_t &el, uint8_t v)
{
  // Translate the given MIDI controller value to the range and stepsize
  // indicated by the Faust control.
  switch (el.type) {
  case UI_BUTTON: case UI_CHECK_BUTTON:
    return (float)(v>=64);
  default:
    /* Continuous controllers. The problem here is that the range 0..127 is
       not symmetric. We'd like to map 64 to the center of the range
       (max-min)/2 and at the same time retain the full control range
       min..max. So let's just pretend that there are 128 controller values
       and map value 127 to the max value anyway. */
    if (v==127)
      return el.max;
    else
      // XXXFIXME: We might want to add proper quantization according to
      // el.step here.
      return el.min+(el.max-el.min)*v/128;
  }
}
#endif

static void
run(LV2_Handle instance, uint32_t n_samples)
{
  LV2Plugin* plugin = (LV2Plugin*)instance;
  int n = plugin->dsp->getNumInputs(), m = plugin->dsp->getNumOutputs();
  AVOIDDENORMALS;
  if (!plugin->active) {
    if (n == m) {
      // copy inputs to outputs
      for (int i = 0; i < m; i++)
	for (unsigned j = 0; j < n_samples; j++)
	  plugin->outputs[i][j] = plugin->inputs[i][j];
    } else {
      // silence
      for (int i = 0; i < m; i++)
	for (unsigned j = 0; j < n_samples; j++)
	  plugin->outputs[i][j] = 0.0f;
    }
    return;
  }
#if FAUST_MIDICC
  if (!plugin->ctrlmap.empty() && plugin->event_port) {
    // Process incoming MIDI events.
    LV2_Atom_Event* i;
    LV2_ATOM_SEQUENCE_FOREACH(plugin->event_port, ev) {
      if (ev->body.type == plugin->midi_event) {
	uint8_t *data = (uint8_t*)(ev+1);
#if DEBUG_MIDI
	fprintf(stderr, "midi ev (%u bytes):", ev->body.size);
	for (unsigned i = 0; i < ev->body.size; i++)
	  fprintf(stderr, " 0x%0x", data[i]);
	fprintf(stderr, "\n");
#endif
	uint8_t status = data[0] & 0xf0, chan = data[0] & 0x0f;
	if (status == 0xb0) {
	  // interpret all other controller changes according to the MIDI
	  // controller map defined in the Faust plugin itself
	  std::map<uint8_t,int>::iterator it = plugin->ctrlmap.find(data[1]);
	  if (it != plugin->ctrlmap.end()) {
	    // defined MIDI controller
	    int j = plugin->inctrls[it->second];
#if DEBUG_MIDICC
	    fprintf(stderr, "ctrl-change chan %d, ctrl %d, val %d\n", chan+1,
		    data[1], data[2]);
#endif
	    *plugin->ui->elems[j].zone = ctrlval(plugin->ui->elems[j], data[2]);
	  }
	}
      } else {
	fprintf(stderr, "%s: unknown event type %d\n", PLUGIN_URI, ev->body.type);
      }
    }
  }
#endif
  // Only update the controls if the port value actually changed. This is
  // necessary to preserve the MIDI controller changes (see above). Also note
  // that we do this *after* processing the MIDI controller data so that
  // manual inputs can override these.
  for (int i = 0; i < plugin->n_in; i++) {
    int j = plugin->inctrls[i], k = plugin->ui->elems[j].port;
    float &oldval = plugin->portvals[k], newval = *plugin->ports[k];
    if (newval != oldval)
      *plugin->ui->elems[j].zone = oldval = newval;
  }
  // Let Faust do all the hard work.
  plugin->dsp->compute(n_samples, plugin->inputs, plugin->outputs);
  // Finally grab the passive controls and write them back to the
  // corresponding LV2 ports.
  for (int i = 0; i < plugin->n_out; i++) {
    int j = plugin->outctrls[i], k = plugin->ui->elems[j].port;
    float *z = plugin->ui->elems[j].zone;
    *plugin->ports[k] = *z;
  }
}

static void
activate(LV2_Handle instance)
{
  LV2Plugin* plugin = (LV2Plugin*)instance;
  plugin->dsp->init(plugin->rate);
  for (int i = 0, j = 0; i < plugin->ui->nelems; i++) {
    int p = plugin->ui->elems[i].port;
    if (p >= 0) {
      float val = plugin->ui->elems[i].init;
      plugin->portvals[p] = val;
    }
  }
  plugin->active = true;
}

static void
deactivate(LV2_Handle instance)
{
  LV2Plugin* plugin = (LV2Plugin*)instance;
  plugin->active = false;
}

const void*
extension_data(const char* uri)
{
  return NULL;
}

static const LV2_Descriptor descriptor = {
  PLUGIN_URI,
  instantiate,
  connect_port,
  activate,
  run,
  deactivate,
  cleanup,
  extension_data
};

extern "C"
LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
  switch (index) {
  case 0:
    return &descriptor;
  default:
    return NULL;
  }
}

//----------------------------------------------------------------------------
//  Dynamic manifest
//----------------------------------------------------------------------------

// NOTE: If your LV2 host doesn't offer this extension then you'll have to
// create a static ttl file with the descriptions of the ports yourself. You
// can also do this by compiling this code to a standalone executable while
// defining the __MAIN__ symbol. Running the executable then prints the
// manifest on stdout.

extern "C"
LV2_SYMBOL_EXPORT
int lv2_dyn_manifest_open(LV2_Dyn_Manifest_Handle *handle,
			  const LV2_Feature *const *features)
{
  LV2Plugin* plugin = new LV2Plugin;
  plugin->dsp = new Prefreak();
  plugin->ui = new LV2UI();
  plugin->dsp->init(48000);
  plugin->dsp->buildUserInterface(plugin->ui);
  int k = plugin->ui->nports;
  plugin->ctrls = (int*)calloc(k, sizeof(int));
  assert(k == 0 || plugin->ctrls);
  for (int i = 0, j = 0; i < plugin->ui->nelems; i++) {
    switch (plugin->ui->elems[i].type) {
    case UI_T_GROUP: case UI_H_GROUP: case UI_V_GROUP: case UI_END_GROUP:
      // control groups
      break;
    case UI_H_BARGRAPH: case UI_V_BARGRAPH:
      // passive controls (output ports)
      plugin->ctrls[j++] = i;
      break;
    default:
      // active controls (input ports)
      plugin->ctrls[j++] = i;
      break;
    }
  }
  *handle = (LV2_Dyn_Manifest_Handle)plugin;
  return 0;
}

extern "C"
LV2_SYMBOL_EXPORT
int lv2_dyn_manifest_get_subjects(LV2_Dyn_Manifest_Handle handle,
				  FILE *fp)
{
  fprintf(fp, "@prefix lv2:  <http://lv2plug.in/ns/lv2core#> .\n\
<%s> a lv2:Plugin .\n", PLUGIN_URI);
  return 0;
}

#include <string>
#include <ctype.h>

static string mangle(const string &s)
{
  string t = s;
  size_t n = s.size();
  for (size_t i = 0; i < n; i++)
    if ((i == 0 && !isalpha(t[i]) && t[i] != '_') ||
	(!isalnum(t[i]) && t[i] != '_'))
      t[i] = '_';
  return t;
}

#if FAUST_META
static bool is_xmlstring(const char *s)
{
  // This is just a basic sanity check. The string must not contain any
  // (unescaped) newlines, carriage returns or double quotes.
  return !strchr(s, '\n') && !strchr(s, '\r') && !strchr(s, '"');
}
#endif

extern "C"
LV2_SYMBOL_EXPORT
int lv2_dyn_manifest_get_data(LV2_Dyn_Manifest_Handle handle,
			      FILE *fp,
			      const char *uri)
{
  LV2Plugin* plugin = (LV2Plugin*)handle;
  int k = plugin->ui->nports;
  int n = plugin->dsp->getNumInputs(), m = plugin->dsp->getNumOutputs();
  // Scan the global metadata for plugin name, description, license etc.
  const char *plugin_name = NULL, *plugin_author = NULL, *plugin_descr = NULL,
    *plugin_license = NULL;
#if FAUST_META
  Meta meta;
  plugin->dsp->metadata(&meta);
  for (std::list<strpair>::iterator it = meta.data.begin();
       it != meta.data.end(); it++) {
    const char *key = it->first, *val = it->second;
    if (!val || !is_xmlstring(val)) continue;
    if (!strcmp(key, "name")) {
      if (!plugin_name)
	plugin_name = val;
    } else if (!strcmp(key, "description")) {
      if (!plugin_descr)
	plugin_descr = val;
    } else if (!strcmp(key, "author")) {
      if (!plugin_author)
	plugin_author = val;
    } else if (!strcmp(key, "license")) {
      if (!plugin_license)
	plugin_license = val;
    }
  }
#endif
  if (!plugin_name) plugin_name = "Prefreak";
  fprintf(fp, "@prefix doap:  <http://usefulinc.com/ns/doap#> .\n\
@prefix foaf:  <http://xmlns.com/foaf/0.1/> .\n\
@prefix lv2:   <http://lv2plug.in/ns/lv2core#> .\n\
@prefix epp:   <http://lv2plug.in/ns/ext/port-props#> .\n\
@prefix atom:  <http://lv2plug.in/ns/ext/atom#> .\n\
@prefix rdf:   <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n\
@prefix rdfs:  <http://www.w3.org/2000/01/rdf-schema#> .\n\
@prefix units: <http://lv2plug.in/ns/extensions/units#> .\n\
<%s>\n\
       a lv2:Plugin ;\n\
       doap:name \"%s\" ;\n\
       lv2:binary <Prefreak.so> ;\n\
       lv2:optionalFeature epp:supportsStrictBounds ;\n\
       lv2:optionalFeature lv2:hardRtCapable ;\n", PLUGIN_URI, plugin_name);
  if (plugin_author)
    fprintf(fp, "\
       doap:maintainer [ foaf:name \"%s\" ] ;\n", plugin_author);
  if (plugin_descr)
    fprintf(fp, "\
       doap:description \"%s\" ;\n", plugin_descr);
  if (plugin_license)
    fprintf(fp, "\
       doap:license \"%s\" ;\n", plugin_license);
  int idx = 0;
  bool have_midi = false;
  // control ports
  for (int i = 0; i < k; i++, idx++) {
    int j = plugin->ctrls[i];
    assert(idx == plugin->ui->elems[j].port);
    fprintf(fp, "%s [\n", idx==0?"    lv2:port":" ,");
    const char *label = plugin->ui->elems[j].label;
    assert(label);
    string sym = mangle(plugin->ui->elems[j].label);
    switch (plugin->ui->elems[j].type) {
    // active controls (input ports)
    case UI_BUTTON: case UI_CHECK_BUTTON:
    fprintf(fp, "\
	a lv2:ControlPort ;\n\
	a lv2:InputPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"%s\" ;\n\
	lv2:name \"%s\" ;\n\
        lv2:portProperty epp:hasStrictBounds ;\n\
        lv2:portProperty lv2:toggled ;\n\
	lv2:default 0.00000 ;\n\
	lv2:minimum 0.00000 ;\n\
	lv2:maximum 1.00000 ;\n", idx, sym.c_str(), label);
      break;
    case UI_NUM_ENTRY: case UI_H_SLIDER: case UI_V_SLIDER:
    fprintf(fp, "\
	a lv2:ControlPort ;\n\
	a lv2:InputPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"%s\" ;\n\
	lv2:name \"%s\" ;\n\
	lv2:default %g ;\n\
	lv2:minimum %g ;\n\
	lv2:maximum %g ;\n", idx, sym.c_str(), label,
	    plugin->ui->elems[j].init,
	    plugin->ui->elems[j].min,
	    plugin->ui->elems[j].max);
      break;
    // passive controls (output ports)
    case UI_H_BARGRAPH: case UI_V_BARGRAPH:
    fprintf(fp, "\
	a lv2:ControlPort ;\n\
	a lv2:OutputPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"%s\" ;\n\
	lv2:name \"%s\" ;\n\
	lv2:default %g ;\n\
	lv2:minimum %g ;\n\
	lv2:maximum %g ;\n", idx, sym.c_str(), label,
	    plugin->ui->elems[j].min,
	    plugin->ui->elems[j].min,
	    plugin->ui->elems[j].max);
      break;
    default:
      assert(0 && "this can't happen");
      break;
    }
    // Scan for Faust control metadata we understand and add corresponding
    // hints to the LV2 description of the port.
    std::map< int, list<strpair> >::iterator it =
      plugin->ui->metadata.find(j);
    if (it != plugin->ui->metadata.end()) {
      for (std::list<strpair>::iterator jt = it->second.begin();
	   jt != it->second.end(); jt++) {
	const char *key = jt->first, *val = jt->second;
#if FAUST_MIDICC
	unsigned num;
	if (!strcmp(key, "midi") && sscanf(val, "ctrl %u", &num) == 1)
	  have_midi = true;
#endif
	if (!strcmp(key, "unit"))
	  fprintf(fp, "\
	units:unit [\n\
            a            units:Unit ;\n\
            units:name   \"%s\" ;\n\
            units:symbol \"%s\" ;\n\
            units:render \"%%f %s\"\n\
	] ;\n", val, val, val);
	if (strcmp(key, "lv2")) continue;
	if (!strcmp(val, "integer"))
	  fprintf(fp, "\
	lv2:portProperty lv2:integer ;\n");
	else if (!strcmp(val, "hidden") || !strcmp(val, "notOnGUI"))
	  fprintf(fp, "\
	lv2:portProperty epp:notOnGUI ;\n");
	else if (!strncmp(val, "scalepoint", 10) ||
		 !strncmp(val, "scalePoint", 10)) {
	  val += 10;
	  if (!isspace(*val)) continue;
	  char *label = (char*)malloc(strlen(val)+1);
	  float point;
	  int pos;
	  while (sscanf(val, "%s %g%n", label, &point, &pos) == 2) {
	    fprintf(fp, "\
	lv2:scalePoint [ rdfs:label \"%s\"; rdf:value %g ] ;\n",
		    label, point);
	    val += pos;
	  }
	  free(label);
	} else
	  fprintf(stderr, "%s: bad port property '%s:%s'\n", PLUGIN_URI,
		  key, val);
      }
    }
    fprintf(fp, "    ]");
  }
  // audio inputs
  for (int i = 0; i < n; i++, idx++)
    fprintf(fp, "%s [\n\
	a lv2:AudioPort ;\n\
	a lv2:InputPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"in%d\" ;\n\
	lv2:name \"in%d\" ;\n\
    ]", idx==0?"    lv2:port":" ,", idx, i, i);
  // audio outputs
  for (int i = 0; i < m; i++, idx++)
    fprintf(fp, "%s [\n\
	a lv2:AudioPort ;\n\
	a lv2:OutputPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"out%d\" ;\n\
	lv2:name \"out%d\" ;\n\
    ]", idx==0?"    lv2:port":" ,", idx, i, i);
  if (have_midi) {
    // midi input
    fprintf(fp, "%s [\n\
	a lv2:InputPort ;\n\
	a atom:AtomPort ;\n\
	atom:bufferType atom:Sequence ;\n\
	atom:supports <http://lv2plug.in/ns/ext/midi#MidiEvent> ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"midiin\" ;\n\
	lv2:name \"midiin\"\n\
    ]", idx==0?"    lv2:port":" ,", idx);
    idx++;
  }
  fprintf(fp, "\n.\n");
  return 0;
}

extern "C"
LV2_SYMBOL_EXPORT
void lv2_dyn_manifest_close(LV2_Dyn_Manifest_Handle handle)
{
  LV2Plugin* plugin = (LV2Plugin*)handle;
  delete plugin->dsp;
  delete plugin->ui;
  delete plugin;
}

int main()
{
  LV2_Dyn_Manifest_Handle handle;
  LV2_Feature **features = { NULL };
  int res = lv2_dyn_manifest_open(&handle, features);
  if (res) return res;
  res = lv2_dyn_manifest_get_data(handle, stdout, PLUGIN_URI);
  return res;
}

#endif
