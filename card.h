#ifndef _CARD
#define _CARD

#include "CursorFeedback.hpp"
#include "FigureFeedback.hpp"
#include "TapFeedback.hpp"
#include "InputGestureTap.hpp"
#include "InputGestureBasicObjects.hpp"
#include "InputGestureBasicFingers.hpp"
#include "InputGestureMyDoubleTap.hpp"
#include "InputGestureMyTap.hpp"

#include <vector>

using namespace std;
using namespace tuio;


class Card : public OnTable < CanDirectObjects < Graphic > >
{
	public:
	int idCard;
	ofRectangle area;
	ofImage texture;
	bool covered;

    Card();
	Card(int id);
    Card(const Card&);

    ~Card();

};

#endif

