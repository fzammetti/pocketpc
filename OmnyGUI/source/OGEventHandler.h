
// *****************************************************************************************************************************
// This class is the event handler base class.  A client should create one
// of these, overriding the appropriate event handler methods, and register
// it with the widget to which it applies.
// *****************************************************************************************************************************
class OGEventHandler {


	public:

    virtual void click()  { }
    virtual void change() { }


};