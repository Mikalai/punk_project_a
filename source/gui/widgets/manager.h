#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <list>

namespace Gui
{
	static const int LeftButton = 1;
	static const int RightButton = 2;
	static const int MiddleButton = 3;

    class Widget;
    class ContainerWidget;
	class AbstractFontManager;
	class AbstractRender;
	class AbstractInputDevice;
    class Graphics::ITexture2DFactory;
    class StyleSet;

	struct ManagerImpl;

	/**
	*	Singletone class that is used as an entry point to the gui data.
	*	It has a set of methods that provided data user input to the gui 
	*	such as MouseMove, MousePress, that should be called in the place,
	*	where this information is available.
	*
	*	To work gui properly, manager during initialization, before any
	*	widget creation should recieve a pointer to the next objects
	*	- AbstractInputDevice (used to get current state of mouse and keyboard)
	*	- AbstractFontManager (used to get sizes of different letters)
	*	- AbstractRender (provide basic functionality to draw geometric primitive: lines, points, quad, textures quads)
	*	- Graphics::ITexture2DFactory (provide method for creating Graphics::ITexture2D instances from file)
	*	
	*	Any container widget can be added to the Manager. When widget is added to the manager,
	*	it start recieving user input, and became visible on the screen.
	*
	*	Gui content can be loaded into the manager from xml file using LoadFromfile.
	*
	*	It can also load StyleSets from xml files.
	*
	*	To find a widget by name it is possible to use FindByName method. To work properly
	*	user should garantee, that all widget will have unique names.
	*/
	class Manager
    {
    public:  
		~Manager();
		void Render();
        void MouseMove(float x, float y, int button);
        void MousePress(float x, float y, int button);
        void MouseRelease(float x, float y, int button);
        void MouseWheel(float x, float y, int delta);
        void KeyDown(float x, float y, int key);
        void KeyUp(float x, float y, int key);
        float GetWindowWidth();
        float GetWindowHeight();
		void SetViewport(float left, float top, float width, float height);
		void SetInputDevice(boost::shared_ptr<AbstractInputDevice> device);
		boost::shared_ptr<AbstractInputDevice> GetInputDevice();
		void SetFontManager(boost::shared_ptr<AbstractFontManager> font);
		boost::shared_ptr<AbstractFontManager> GetFontManager();
		void SetRender(boost::shared_ptr<AbstractRender> render);
		boost::shared_ptr<AbstractRender> GetRender();
        void SetPictureFactory(boost::shared_ptr<Graphics::ITexture2DFactory> value);
        boost::shared_ptr<Graphics::ITexture2DFactory> GetPictureFactory();
        boost::shared_ptr<StyleSet> GetStyleSet(const std::string& name);
		void Update(float dt);
        void AddWidget(boost::shared_ptr<ContainerWidget> value);
        void RemoveWidget(boost::shared_ptr<ContainerWidget> value);
		boost::shared_ptr<Widget> FindByName(const std::string& name);

		static boost::scoped_ptr<Manager>& Instance();
		static void Destroy();

		boost::scoped_ptr<ManagerImpl> impl;  

        void LoadFromFile(const std::string& filename);
        void LoadStyleSet(const std::string& filename);

	private:

		Manager();		

		static boost::scoped_ptr<Manager> m_instance;
    };

    template<class T>
	boost::shared_ptr<T> cast(const boost::shared_ptr<Widget>& o)
    {
        return boost::dynamic_pointer_cast<T, Widget>(o);
    }
}

#endif // GUI_MANAGER_H
