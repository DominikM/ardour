#include "ardour/warper.h"
#include <cstddef>
#include <rubberband/RubberBandStretcher.h>

using namespace std;
using namespace ARDOUR;

RubberBandWarper::RubberBandWarper (size_t sampleRate, size_t channels, int options, double initialTimeRatio, double initialPitchScale)
	: rbs (sampleRate, channels, options, initialTimeRatio, initialPitchScale),
	  key_frame_map ()
{
}

void
RubberBandWarper::setDebugLevel (int level)
{
	rbs.setDebugLevel(level);
}

void
RubberBandWarper::setExpectedInputDuration (size_t samples)
{
	rbs.setExpectedInputDuration(samples);
}

void
RubberBandWarper::setMaxProcessSize (size_t samples)
{
	rbs.setMaxProcessSize(samples);
}

size_t
RubberBandWarper::getLatency () const
{
	return rbs.getLatency();
}

void
RubberBandWarper::study (const float *const * input, size_t samples, bool final)
{
	rbs.study(input, samples, final);
}

size_t
RubberBandWarper::getSamplesRequired () const
{
	return rbs.getSamplesRequired();
}

void
RubberBandWarper::process (const float *const * input, size_t samples, bool final)
{
	return rbs.process(input, samples, final);
}

int
RubberBandWarper::available () const
{
	return rbs.available();
}

size_t
RubberBandWarper::retrieve (float *const * output, size_t samples) const
{
	return rbs.retrieve(output, samples);
}

void
RubberBandWarper::addKeyFrame(size_t input_position, size_t output_position)
{
	if (key_frame_map.find(input_position) == key_frame_map.end()) {
		key_frame_map[input_position] = output_position;
	}
}

void
RubberBandWarper::updateKeyFrame(size_t input_position, size_t output_position)
{
	if (key_frame_map.find(input_position) != key_frame_map.end()) {
		key_frame_map[input_position] = output_position;
	}
}

void
RubberBandWarper::removeKeyFrame(size_t input_position)
{
	if (key_frame_map.find(input_position) != key_frame_map.end()) {
		key_frame_map.erase(input_position);
	}
}

bool
RubberBandWarper::canRealtimeWarp() const
{
	return false;
}
