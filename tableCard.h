#ifndef _TABLECARD
#define _TABLECARD

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


class TableCard : public OnTable < CanDirectObjects < Graphic > >
{
public:
	int idCard;
	ofRectangle area;
	ofImage texture;
	bool covered;
    bool drawCard;
	ofImage back;

    TableCard();
	TableCard(int id);
    TableCard(const TableCard&);

    ~TableCard();


    void draw();

};

#endif

