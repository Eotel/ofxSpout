#pragma once

#include "ofLog.h"
#include "ofTexture.h"
#include <string>
#include <vector>

class SpoutReceiver;

namespace ofxSpout {
	class Receiver {
	public:
		Receiver();
		~Receiver();

		bool init(std::string channelName = "");
		void release();
		bool isInitialized() const;

		bool receive(ofTexture &); // will automatically allocate the texture

		bool selectSenderPanel();

		std::string getChannelName() const;
		float getWidth() const;
		float getHeight() const;

		// Sender enumeration methods
		void setReceiverName(const std::string& name);
		int getSenderCount() const;
		std::string getSenderName(int index) const;
		std::vector<std::string> getSenderList() const;

	protected:
		SpoutReceiver * spoutReceiver;

		const int defaultFormat; // = GL_RGBA. If you're using anything else then make sure to allocate your texture manually
	};
}
