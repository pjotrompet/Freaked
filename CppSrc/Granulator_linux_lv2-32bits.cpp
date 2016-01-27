/* ------------------------------------------------------------
author: "Mayank Sanganeria"
name: "Granulator"
version: "1.2"
Code generated with Faust 2.0.a40 (http://faust.grame.fr)
------------------------------------------------------------ */

#ifndef  __Granulator_H__
#define  __Granulator_H__
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

#include <math.h>


class GranulatorSIG0 {

  public:


  public:

	int getNumInputsGranulatorSIG0() {
		return 0;

	}
	int getNumOutputsGranulatorSIG0() {
		return 1;

	}
	int getInputRateGranulatorSIG0(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}

		}
		return rate;

	}
	int getOutputRateGranulatorSIG0(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}

		}
		return rate;

	}

	void instanceInitGranulatorSIG0(int samplingFreq) {

	}

	void fillGranulatorSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			output[i] = 0.f;

		}

	}
};

GranulatorSIG0* newGranulatorSIG0() {return (GranulatorSIG0*) new GranulatorSIG0(); }
void deleteGranulatorSIG0(GranulatorSIG0* dsp) {delete dsp; }


#ifndef FAUSTCLASS
#define FAUSTCLASS Granulator
#endif

class Granulator : public dsp {

  public:

	float ftbl0[480000];
	float ftbl1[480000];
	int iVec0[2];
	float fRec0[2];
	float fRec2[2];
	int iRec1[2];
	float fRec4[2];
	int iRec3[2];
	int iRec6[2];
	int iRec5[2];
	int iRec22[2];
	int iRec23[2];
	int iRec24[2];
	int iRec25[2];
	int iRec26[2];
	int iRec27[2];
	int iRec28[2];
	int iRec29[2];
	int iRec30[2];
	int iRec31[2];
	int iRec32[2];
	int iRec33[2];
	int iRec34[2];
	int iRec35[2];
	int iRec36[2];
	int iRec37[2];
	int iRec38[2];
	int iRec39[2];
	int iRec40[2];
	int iRec41[2];
	int iRec42[2];
	int iRec43[2];
	int iRec44[2];
	int iRec45[2];
	int iRec46[2];
	int iRec47[2];
	int iRec48[2];
	int iRec49[2];
	int iRec50[2];
	int iRec51[2];
	int iRec52[2];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int fSamplingFreq;
	int iConst0;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;

  public:

	void static metadata(Meta* m) {
		m->declare("author", "Mayank Sanganeria");
		m->declare("compilation_options", "-single -vec -vs 128 -mcd 64");
		m->declare("filter_lib_author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter_lib_copyright", "Julius O. Smith III");
		m->declare("filter_lib_license", "STK-4.3");
		m->declare("filter_lib_name", "Faust Filter Library");
		m->declare("filter_lib_reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("filter_lib_version", "1.29");
		m->declare("library_path", "granulator");
		m->declare("maintainer", "Pjotr Lasschuit");
		m->declare("math_lib_author", "GRAME");
		m->declare("math_lib_copyright", "GRAME");
		m->declare("math_lib_license", "LGPL with exception");
		m->declare("math_lib_name", "Math Library");
		m->declare("math_lib_version", "1.0");
		m->declare("music_lib_author", "GRAME");
		m->declare("music_lib_copyright", "GRAME");
		m->declare("music_lib_license", "LGPL with exception");
		m->declare("music_lib_name", "Music Library");
		m->declare("music_lib_version", "1.0");
		m->declare("name", "Granulator");
		m->declare("version", "1.2");
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
		for (int i0 = 0; (i0 < 2); i0 = (i0 + 1)) {
			iVec0[i0] = 0;

		}
		fHslider0 = FAUSTFLOAT(0.5);
		for (int i1 = 0; (i1 < 2); i1 = (i1 + 1)) {
			fRec0[i1] = 0.f;

		}
		fHslider1 = FAUSTFLOAT(2.);
		GranulatorSIG0* sig0 = newGranulatorSIG0();
		sig0->instanceInitGranulatorSIG0(samplingFreq);
		sig0->fillGranulatorSIG0(480000, ftbl0);
		iConst0 = min(192000, max(1, fSamplingFreq));
		fHslider2 = FAUSTFLOAT(10.);
		for (int i2 = 0; (i2 < 2); i2 = (i2 + 1)) {
			fRec2[i2] = 0.f;

		}
		for (int i3 = 0; (i3 < 2); i3 = (i3 + 1)) {
			iRec1[i3] = 0;

		}
		fHslider3 = FAUSTFLOAT(0.1);
		for (int i4 = 0; (i4 < 2); i4 = (i4 + 1)) {
			fRec4[i4] = 0.f;

		}
		for (int i5 = 0; (i5 < 2); i5 = (i5 + 1)) {
			iRec3[i5] = 0;

		}
		for (int i6 = 0; (i6 < 2); i6 = (i6 + 1)) {
			iRec6[i6] = 0;

		}
		for (int i7 = 0; (i7 < 2); i7 = (i7 + 1)) {
			iRec5[i7] = 0;

		}
		for (int i8 = 0; (i8 < 2); i8 = (i8 + 1)) {
			iRec22[i8] = 0;

		}
		for (int i9 = 0; (i9 < 2); i9 = (i9 + 1)) {
			iRec23[i9] = 0;

		}
		for (int i10 = 0; (i10 < 2); i10 = (i10 + 1)) {
			iRec24[i10] = 0;

		}
		for (int i11 = 0; (i11 < 2); i11 = (i11 + 1)) {
			iRec25[i11] = 0;

		}
		for (int i12 = 0; (i12 < 2); i12 = (i12 + 1)) {
			iRec26[i12] = 0;

		}
		for (int i13 = 0; (i13 < 2); i13 = (i13 + 1)) {
			iRec27[i13] = 0;

		}
		for (int i14 = 0; (i14 < 2); i14 = (i14 + 1)) {
			iRec28[i14] = 0;

		}
		for (int i15 = 0; (i15 < 2); i15 = (i15 + 1)) {
			iRec29[i15] = 0;

		}
		for (int i16 = 0; (i16 < 2); i16 = (i16 + 1)) {
			iRec30[i16] = 0;

		}
		for (int i17 = 0; (i17 < 2); i17 = (i17 + 1)) {
			iRec31[i17] = 0;

		}
		for (int i18 = 0; (i18 < 2); i18 = (i18 + 1)) {
			iRec32[i18] = 0;

		}
		for (int i19 = 0; (i19 < 2); i19 = (i19 + 1)) {
			iRec33[i19] = 0;

		}
		for (int i20 = 0; (i20 < 2); i20 = (i20 + 1)) {
			iRec34[i20] = 0;

		}
		for (int i21 = 0; (i21 < 2); i21 = (i21 + 1)) {
			iRec35[i21] = 0;

		}
		for (int i22 = 0; (i22 < 2); i22 = (i22 + 1)) {
			iRec36[i22] = 0;

		}
		sig0->instanceInitGranulatorSIG0(samplingFreq);
		sig0->fillGranulatorSIG0(480000, ftbl1);
		for (int i23 = 0; (i23 < 2); i23 = (i23 + 1)) {
			iRec37[i23] = 0;

		}
		for (int i24 = 0; (i24 < 2); i24 = (i24 + 1)) {
			iRec38[i24] = 0;

		}
		for (int i25 = 0; (i25 < 2); i25 = (i25 + 1)) {
			iRec39[i25] = 0;

		}
		for (int i26 = 0; (i26 < 2); i26 = (i26 + 1)) {
			iRec40[i26] = 0;

		}
		for (int i27 = 0; (i27 < 2); i27 = (i27 + 1)) {
			iRec41[i27] = 0;

		}
		for (int i28 = 0; (i28 < 2); i28 = (i28 + 1)) {
			iRec42[i28] = 0;

		}
		for (int i29 = 0; (i29 < 2); i29 = (i29 + 1)) {
			iRec43[i29] = 0;

		}
		for (int i30 = 0; (i30 < 2); i30 = (i30 + 1)) {
			iRec44[i30] = 0;

		}
		for (int i31 = 0; (i31 < 2); i31 = (i31 + 1)) {
			iRec45[i31] = 0;

		}
		for (int i32 = 0; (i32 < 2); i32 = (i32 + 1)) {
			iRec46[i32] = 0;

		}
		for (int i33 = 0; (i33 < 2); i33 = (i33 + 1)) {
			iRec47[i33] = 0;

		}
		for (int i34 = 0; (i34 < 2); i34 = (i34 + 1)) {
			iRec48[i34] = 0;

		}
		for (int i35 = 0; (i35 < 2); i35 = (i35 + 1)) {
			iRec49[i35] = 0;

		}
		for (int i36 = 0; (i36 < 2); i36 = (i36 + 1)) {
			iRec50[i36] = 0;

		}
		for (int i37 = 0; (i37 < 2); i37 = (i37 + 1)) {
			iRec51[i37] = 0;

		}
		for (int i38 = 0; (i38 < 2); i38 = (i38 + 1)) {
			iRec52[i38] = 0;

		}
		deleteGranulatorSIG0(sig0);

	}

	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}

	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("0x00");
		interface->addHorizontalSlider("delay length", &fHslider2, 10.f, 0.5f, 10.f, 0.1f);
		interface->addHorizontalSlider("grain density", &fHslider1, 2.f, 2.f, 16.f, 1.f);
		interface->addHorizontalSlider("grain length", &fHslider3, 0.1f, 0.01f, 0.5f, 0.01f);
		interface->addHorizontalSlider("mix", &fHslider0, 0.5f, 0.f, 1.f, 0.01f);
		interface->closeBox();

	}

	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.001f * float(fHslider0));
		float fSlow1 = float(fHslider1);
		int iSlow2 = (0.f < fSlow1);
		float fSlow3 = (0.001f * float(fHslider2));
		float fSlow4 = (0.001f * float(fHslider3));
		int iSlow5 = (2.f < fSlow1);
		int iSlow6 = (4.f < fSlow1);
		int iSlow7 = (6.f < fSlow1);
		int iSlow8 = (8.f < fSlow1);
		int iSlow9 = (10.f < fSlow1);
		int iSlow10 = (12.f < fSlow1);
		int iSlow11 = (14.f < fSlow1);
		int iSlow12 = (1.f < fSlow1);
		int iSlow13 = (3.f < fSlow1);
		int iSlow14 = (5.f < fSlow1);
		int iSlow15 = (7.f < fSlow1);
		int iSlow16 = (9.f < fSlow1);
		int iSlow17 = (11.f < fSlow1);
		int iSlow18 = (13.f < fSlow1);
		int iSlow19 = (15.f < fSlow1);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec0[0] = ((0.999f * fRec0[1]) + fSlow0);
			float fTemp0 = (1.f - fRec0[0]);
			float fTemp1 = float(input0[i]);
			fRec2[0] = ((0.999f * fRec2[1]) + fSlow3);
			int iTemp2 = int((float(iConst0) * fRec2[0]));
			iRec1[0] = ((1 % iTemp2) + iRec1[1]);
			int iTemp3 = (iRec1[0] % iTemp2);
			ftbl0[iTemp3] = fTemp1;
			fRec4[0] = ((0.999f * fRec4[1]) + fSlow4);
			int iTemp4 = int((float(iConst0) * fRec4[0]));
			iRec3[0] = ((1 + iRec3[1]) % iTemp4);
			int iTemp5 = (1 - iVec0[1]);
			int iTemp6 = (1103515245 * (12345 + iRec6[1]));
			int iTemp7 = (1103515245 * (12345 + iTemp6));
			int iTemp8 = (1103515245 * (12345 + iTemp7));
			int iTemp9 = (1103515245 * (12345 + iTemp8));
			int iTemp10 = (1103515245 * (12345 + iTemp9));
			int iTemp11 = (1103515245 * (12345 + iTemp10));
			int iTemp12 = (1103515245 * (12345 + iTemp11));
			int iTemp13 = (1103515245 * (12345 + iTemp12));
			int iTemp14 = (1103515245 * (12345 + iTemp13));
			int iTemp15 = (1103515245 * (12345 + iTemp14));
			int iTemp16 = (1103515245 * (12345 + iTemp15));
			int iTemp17 = (1103515245 * (12345 + iTemp16));
			int iTemp18 = (1103515245 * (12345 + iTemp17));
			int iTemp19 = (1103515245 * (12345 + iTemp18));
			int iTemp20 = (1103515245 * (12345 + iTemp19));
			int iTemp21 = (1103515245 * (12345 + iTemp20));
			iRec6[0] = (1103515245 * (12345 + iTemp21));
			int iRec7 = iTemp21;
			int iRec8 = iTemp20;
			int iRec9 = iTemp19;
			int iRec10 = iTemp18;
			int iRec11 = iTemp17;
			int iRec12 = iTemp16;
			int iRec13 = iTemp15;
			int iRec14 = iTemp14;
			int iRec15 = iTemp13;
			int iRec16 = iTemp12;
			int iRec17 = iTemp11;
			int iRec18 = iTemp10;
			int iRec19 = iTemp9;
			int iRec20 = iTemp8;
			int iRec21 = iTemp7;
			int iTemp22 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec6[0]))))));
			iRec5[0] = ((iRec5[1] * iVec0[1]) + (iTemp5 * iTemp22));
			int iTemp23 = ((iRec3[0] + iRec5[0]) % iTemp4);
			int iTemp24 = (iTemp4 - 1);
			float fTemp25 = (float(iTemp23) / float(iTemp24));
			int iTemp26 = int(fTemp25);
			iRec22[0] = (((1 - iTemp26) * iRec22[1]) + (iTemp26 * iTemp22));
			int iTemp27 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec8))))));
			iRec23[0] = ((iVec0[1] * iRec23[1]) + (iTemp5 * iTemp27));
			int iTemp28 = ((iRec3[0] + iRec23[0]) % iTemp4);
			float fTemp29 = (float(iTemp28) / float(iTemp24));
			int iTemp30 = int(fTemp29);
			iRec24[0] = (((1 - iTemp30) * iRec24[1]) + (iTemp30 * iTemp27));
			int iTemp31 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec10))))));
			iRec25[0] = ((iVec0[1] * iRec25[1]) + (iTemp5 * iTemp31));
			int iTemp32 = ((iRec3[0] + iRec25[0]) % iTemp4);
			float fTemp33 = (float(iTemp32) / float(iTemp24));
			int iTemp34 = int(fTemp33);
			iRec26[0] = (((1 - iTemp34) * iRec26[1]) + (iTemp34 * iTemp31));
			int iTemp35 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec12))))));
			iRec27[0] = ((iVec0[1] * iRec27[1]) + (iTemp5 * iTemp35));
			int iTemp36 = ((iRec3[0] + iRec27[0]) % iTemp4);
			float fTemp37 = (float(iTemp36) / float(iTemp24));
			int iTemp38 = int(fTemp37);
			iRec28[0] = (((1 - iTemp38) * iRec28[1]) + (iTemp38 * iTemp35));
			int iTemp39 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec14))))));
			iRec29[0] = ((iVec0[1] * iRec29[1]) + (iTemp5 * iTemp39));
			int iTemp40 = ((iRec3[0] + iRec29[0]) % iTemp4);
			float fTemp41 = (float(iTemp40) / float(iTemp24));
			int iTemp42 = int(fTemp41);
			iRec30[0] = (((1 - iTemp42) * iRec30[1]) + (iTemp42 * iTemp39));
			int iTemp43 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec16))))));
			iRec31[0] = ((iVec0[1] * iRec31[1]) + (iTemp5 * iTemp43));
			int iTemp44 = ((iRec3[0] + iRec31[0]) % iTemp4);
			float fTemp45 = (float(iTemp44) / float(iTemp24));
			int iTemp46 = int(fTemp45);
			iRec32[0] = (((1 - iTemp46) * iRec32[1]) + (iTemp46 * iTemp43));
			int iTemp47 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec18))))));
			iRec33[0] = ((iVec0[1] * iRec33[1]) + (iTemp5 * iTemp47));
			int iTemp48 = ((iRec3[0] + iRec33[0]) % iTemp4);
			float fTemp49 = (float(iTemp48) / float(iTemp24));
			int iTemp50 = int(fTemp49);
			iRec34[0] = (((1 - iTemp50) * iRec34[1]) + (iTemp50 * iTemp47));
			int iTemp51 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec20))))));
			iRec35[0] = ((iVec0[1] * iRec35[1]) + (iTemp5 * iTemp51));
			int iTemp52 = ((iRec3[0] + iRec35[0]) % iTemp4);
			float fTemp53 = (float(iTemp52) / float(iTemp24));
			int iTemp54 = int(fTemp53);
			iRec36[0] = (((1 - iTemp54) * iRec36[1]) + (iTemp54 * iTemp51));
			output0[i] = FAUSTFLOAT(((fTemp0 * fTemp1) + (2.f * (fRec0[0] * ((((((((float(iSlow2) * (ftbl0[((iTemp23 + iRec22[0]) % iTemp2)] * sinf((6.28318f * fTemp25)))) + (float(iSlow5) * (ftbl0[((iTemp28 + iRec24[0]) % iTemp2)] * sinf((6.28318f * fTemp29))))) + (float(iSlow6) * (ftbl0[((iTemp32 + iRec26[0]) % iTemp2)] * sinf((6.28318f * fTemp33))))) + (float(iSlow7) * (ftbl0[((iTemp36 + iRec28[0]) % iTemp2)] * sinf((6.28318f * fTemp37))))) + (float(iSlow8) * (ftbl0[((iTemp40 + iRec30[0]) % iTemp2)] * sinf((6.28318f * fTemp41))))) + (float(iSlow9) * (ftbl0[((iTemp44 + iRec32[0]) % iTemp2)] * sinf((6.28318f * fTemp45))))) + (float(iSlow10) * (ftbl0[((iTemp48 + iRec34[0]) % iTemp2)] * sinf((6.28318f * fTemp49))))) + (float(iSlow11) * (ftbl0[((iTemp52 + iRec36[0]) % iTemp2)] * sinf((6.28318f * fTemp53)))))))));
			float fTemp55 = float(input1[i]);
			ftbl1[iTemp3] = fTemp55;
			int iTemp56 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec7))))));
			iRec37[0] = ((iVec0[1] * iRec37[1]) + (iTemp5 * iTemp56));
			int iTemp57 = ((iRec3[0] + iRec37[0]) % iTemp4);
			float fTemp58 = (float(iTemp57) / float(iTemp24));
			int iTemp59 = int(fTemp58);
			iRec38[0] = (((1 - iTemp59) * iRec38[1]) + (iTemp59 * iTemp56));
			int iTemp60 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec9))))));
			iRec39[0] = ((iVec0[1] * iRec39[1]) + (iTemp5 * iTemp60));
			int iTemp61 = ((iRec3[0] + iRec39[0]) % iTemp4);
			float fTemp62 = (float(iTemp61) / float(iTemp24));
			int iTemp63 = int(fTemp62);
			iRec40[0] = (((1 - iTemp63) * iRec40[1]) + (iTemp63 * iTemp60));
			int iTemp64 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec11))))));
			iRec41[0] = ((iVec0[1] * iRec41[1]) + (iTemp5 * iTemp64));
			int iTemp65 = ((iRec3[0] + iRec41[0]) % iTemp4);
			float fTemp66 = (float(iTemp65) / float(iTemp24));
			int iTemp67 = int(fTemp66);
			iRec42[0] = (((1 - iTemp67) * iRec42[1]) + (iTemp67 * iTemp64));
			int iTemp68 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec13))))));
			iRec43[0] = ((iVec0[1] * iRec43[1]) + (iTemp5 * iTemp68));
			int iTemp69 = ((iRec3[0] + iRec43[0]) % iTemp4);
			float fTemp70 = (float(iTemp69) / float(iTemp24));
			int iTemp71 = int(fTemp70);
			iRec44[0] = (((1 - iTemp71) * iRec44[1]) + (iTemp71 * iTemp68));
			int iTemp72 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec15))))));
			iRec45[0] = ((iVec0[1] * iRec45[1]) + (iTemp5 * iTemp72));
			int iTemp73 = ((iRec3[0] + iRec45[0]) % iTemp4);
			float fTemp74 = (float(iTemp73) / float(iTemp24));
			int iTemp75 = int(fTemp74);
			iRec46[0] = (((1 - iTemp75) * iRec46[1]) + (iTemp75 * iTemp72));
			int iTemp76 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec17))))));
			iRec47[0] = ((iVec0[1] * iRec47[1]) + (iTemp5 * iTemp76));
			int iTemp77 = ((iRec3[0] + iRec47[0]) % iTemp4);
			float fTemp78 = (float(iTemp77) / float(iTemp24));
			int iTemp79 = int(fTemp78);
			iRec48[0] = (((1 - iTemp79) * iRec48[1]) + (iTemp79 * iTemp76));
			int iTemp80 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec19))))));
			iRec49[0] = ((iVec0[1] * iRec49[1]) + (iTemp5 * iTemp80));
			int iTemp81 = ((iRec3[0] + iRec49[0]) % iTemp4);
			float fTemp82 = (float(iTemp81) / float(iTemp24));
			int iTemp83 = int(fTemp82);
			iRec50[0] = (((1 - iTemp83) * iRec50[1]) + (iTemp83 * iTemp80));
			int iTemp84 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec21))))));
			iRec51[0] = ((iVec0[1] * iRec51[1]) + (iTemp5 * iTemp84));
			int iTemp85 = ((iRec3[0] + iRec51[0]) % iTemp4);
			float fTemp86 = (float(iTemp85) / float(iTemp24));
			int iTemp87 = int(fTemp86);
			iRec52[0] = (((1 - iTemp87) * iRec52[1]) + (iTemp87 * iTemp84));
			output1[i] = FAUSTFLOAT(((fTemp0 * fTemp55) + (2.f * (fRec0[0] * ((((((((float(iSlow12) * (ftbl1[((iTemp57 + iRec38[0]) % iTemp2)] * sinf((6.28318f * fTemp58)))) + (float(iSlow13) * (ftbl1[((iTemp61 + iRec40[0]) % iTemp2)] * sinf((6.28318f * fTemp62))))) + (float(iSlow14) * (ftbl1[((iTemp65 + iRec42[0]) % iTemp2)] * sinf((6.28318f * fTemp66))))) + (float(iSlow15) * (ftbl1[((iTemp69 + iRec44[0]) % iTemp2)] * sinf((6.28318f * fTemp70))))) + (float(iSlow16) * (ftbl1[((iTemp73 + iRec46[0]) % iTemp2)] * sinf((6.28318f * fTemp74))))) + (float(iSlow17) * (ftbl1[((iTemp77 + iRec48[0]) % iTemp2)] * sinf((6.28318f * fTemp78))))) + (float(iSlow18) * (ftbl1[((iTemp81 + iRec50[0]) % iTemp2)] * sinf((6.28318f * fTemp82))))) + (float(iSlow19) * (ftbl1[((iTemp85 + iRec52[0]) % iTemp2)] * sinf((6.28318f * fTemp86)))))))));
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			iRec1[1] = iRec1[0];
			fRec4[1] = fRec4[0];
			iRec3[1] = iRec3[0];
			iRec6[1] = iRec6[0];
			iRec5[1] = iRec5[0];
			iRec22[1] = iRec22[0];
			iRec23[1] = iRec23[0];
			iRec24[1] = iRec24[0];
			iRec25[1] = iRec25[0];
			iRec26[1] = iRec26[0];
			iRec27[1] = iRec27[0];
			iRec28[1] = iRec28[0];
			iRec29[1] = iRec29[0];
			iRec30[1] = iRec30[0];
			iRec31[1] = iRec31[0];
			iRec32[1] = iRec32[0];
			iRec33[1] = iRec33[0];
			iRec34[1] = iRec34[0];
			iRec35[1] = iRec35[0];
			iRec36[1] = iRec36[0];
			iRec37[1] = iRec37[0];
			iRec38[1] = iRec38[0];
			iRec39[1] = iRec39[0];
			iRec40[1] = iRec40[0];
			iRec41[1] = iRec41[0];
			iRec42[1] = iRec42[0];
			iRec43[1] = iRec43[0];
			iRec44[1] = iRec44[0];
			iRec45[1] = iRec45[0];
			iRec46[1] = iRec46[0];
			iRec47[1] = iRec47[0];
			iRec48[1] = iRec48[0];
			iRec49[1] = iRec49[0];
			iRec50[1] = iRec50[0];
			iRec51[1] = iRec51[0];
			iRec52[1] = iRec52[0];

		}

	}


};


#ifdef FAUST_UIMACROS
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 4
	#define FAUST_PASSIVES 0
	FAUST_ADDHORIZONTALSLIDER("delay length", fHslider2, 1e+01f, 0.5f, 1e+01f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("grain density", fHslider1, 2.0f, 2.0f, 16.0f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("grain length", fHslider3, 0.1f, 0.01f, 0.5f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("mix", fHslider0, 0.5f, 0.0f, 1.0f, 0.01f);
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
#define PLUGIN_URI URI_PREFIX "/Granulator"
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
  Granulator *dsp;		// the dsp
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
  plugin->dsp = new Granulator();
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
  plugin->dsp = new Granulator();
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
  if (!plugin_name) plugin_name = "Granulator";
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
       lv2:binary <Granulator.so> ;\n\
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
