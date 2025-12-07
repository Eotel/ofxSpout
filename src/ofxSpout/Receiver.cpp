#include "Receiver.h"
#include "ofGraphics.h"
#include "Utils.h"

#include "gl/glew.h"
#include "SpoutReceiver.h"

namespace ofxSpout {
	//----------
	Receiver::Receiver() :
		defaultFormat(GL_RGBA) {
		this->spoutReceiver = nullptr;
	}

	//----------
	Receiver::~Receiver() {
		this->release();
	}

	//----------
	bool Receiver::init(std::string channelName) {
		this->release();

		try {
			this->spoutReceiver = new SpoutReceiver();
			//name provided, so let's use it
			if (!channelName.empty()) {
				this->spoutReceiver->SetReceiverName(channelName.c_str());
			}

			return true;
		}
		catch (const char * e) {
			ofLogError(__FUNCTION__) << "Channel : " << channelName << " : " << e;
			return false;
		}
	}

	//----------
	void Receiver::release() {
		if (this->isInitialized()) {
			this->spoutReceiver->ReleaseReceiver();
			delete this->spoutReceiver;
			this->spoutReceiver = nullptr;
		}
	}

	//----------
	bool Receiver::isInitialized() const {
		if (this->spoutReceiver) {
			return true;
		}
		else {
			return false;
		}
	}

	//----------
	bool Receiver::receive(ofTexture & texture) {
		try {
			//check if we're initialised
			if (!this->isInitialized()) {
				throw("Not initialized");
			}

			if (this->spoutReceiver->ReceiveTexture()) {
				// Update the receiving texture if the received size has changed
				if (this->spoutReceiver->IsUpdated()) {
					texture.allocate(this->spoutReceiver->GetSenderWidth(), this->spoutReceiver->GetSenderHeight(), this->spoutReceiver->GLDXformat());
					return false; // Return now because the texture will empty
				}
				// Bind to get access to the shared texture
				if (this->spoutReceiver->BindSharedTexture()) {
					// Copy from the shared texture 
					this->spoutReceiver->CopyTexture(this->spoutReceiver->GetSharedTextureID(), GL_TEXTURE_2D,
						texture.getTextureData().textureID,
						texture.getTextureData().textureTarget,
						this->spoutReceiver->GetSenderWidth(), this->spoutReceiver->GetSenderHeight());
					// Un-bind to release access to the shared texture
					this->spoutReceiver->UnBindSharedTexture();
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}

			return true;
		}
		catch (const char * e) {
			ofLogError(__FUNCTION__) << e;
			return false;
		}
	}

	//----------
	bool Receiver::selectSenderPanel() {
		try {
			if (!this->isInitialized()) {
				throw("Not initialized");
			}
			this->spoutReceiver->SelectSender();
			return true;
		}
		catch (const char * e) {
			ofLogError(__FUNCTION__) << e;
			return false;
		}
	}
	
	//-----------
	std::string Receiver::getChannelName() const {
		if (this->isInitialized()) {
			return this->spoutReceiver->GetSenderName();
		}
		return "";
	}

	//----------
	float Receiver::getWidth() const {
		if (this->isInitialized()) {
			return this->spoutReceiver->GetSenderWidth();
		}
		return 0;
	}

	//----------
	float Receiver::getHeight() const {
		if (this->isInitialized()) {
			return this->spoutReceiver->GetSenderHeight();
		}
		return 0;
	}

	//----------
	void Receiver::setReceiverName(const std::string& name) {
		if (this->isInitialized()) {
			this->spoutReceiver->SetReceiverName(name.c_str());
		}
	}

	//----------
	int Receiver::getSenderCount() const {
		if (this->isInitialized()) {
			return this->spoutReceiver->GetSenderCount();
		}
		return 0;
	}

	//----------
	std::string Receiver::getSenderName(int index) const {
		if (this->isInitialized()) {
			char name[256];
			if (this->spoutReceiver->GetSender(index, name, 256)) {
				return std::string(name);
			}
		}
		return "";
	}

	//----------
	std::vector<std::string> Receiver::getSenderList() const {
		if (this->isInitialized()) {
			return this->spoutReceiver->GetSenderList();
		}
		return {};
	}
}