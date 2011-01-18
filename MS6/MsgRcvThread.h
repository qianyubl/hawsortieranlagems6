#include "HAWThread.h"
#include "Automat.h"
#include <vector>

class MsgRcvThread : public thread::HAWThread
{
public:
	MsgRcvThread();
	~MsgRcvThread();
	virtual void execute(void*);

	/**
	 * shuts the thread down
	 *
	 * @no Arg
	 */
	virtual void shutdown();
	void init(int channelID);

private:
	int chid;
	int msg;
	int newMsg;
	int switched;
	int flanke;
	std::vector<Automat*> automatenListe;
	//david hausnummer 04064661219
};

