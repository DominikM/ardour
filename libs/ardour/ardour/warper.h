#ifndef __libardour_warper_h__
#define __libardour_warper_h__

#include "ardour/libardour_visibility.h"
#include <cstddef>
#include <rubberband/RubberBandStretcher.h>
#include <unordered_map>

namespace ARDOUR {

class LIBARDOUR_API Warper
{
public:
	virtual void setDebugLevel (int level) = 0;
	virtual void setExpectedInputDuration (size_t samples) = 0;
	virtual void setMaxProcessSize (size_t samples) = 0;
	virtual size_t getLatency () const = 0;
	virtual void study (const float *const * input, size_t samples, bool final) = 0;
	virtual size_t getSamplesRequired () const = 0;
	virtual void process (const float *const * input, size_t samples, bool final) = 0;
	virtual int available () const = 0;
	virtual size_t retrieve (float *const * output, size_t samples) const = 0;
	virtual void addKeyFrame(size_t input_position, size_t output_position) = 0;
	virtual void updateKeyFrame(size_t input_position, size_t output_position) = 0;
	virtual void removeKeyFrame(size_t input_position) = 0;
	virtual bool canRealtimeWarp() const = 0;
};

class LIBARDOUR_API RubberBandWarper : public Warper
{
public:
	RubberBandWarper (size_t sampleRate, size_t channels, int options, double initialTimeRatio = 1.0, double initialPitchScale = 1.0);
	void setDebugLevel (int level);
	void setExpectedInputDuration (size_t samples);
	void setMaxProcessSize (size_t samples);
	size_t getLatency () const;
	void study (const float *const * input, size_t samples, bool final);
	size_t getSamplesRequired () const;
	void process (const float *const * input, size_t samples, bool final);
	int available () const;
	size_t retrieve (float *const * output, size_t samples) const;
	void addKeyFrame(size_t input_position, size_t output_position);
	void updateKeyFrame(size_t input_position, size_t output_position);
	void removeKeyFrame(size_t input_position);
	bool canRealtimeWarp() const;
private:
	RubberBand::RubberBandStretcher rbs;
	std::unordered_map<size_t, size_t> key_frame_map;
};

}

#endif
