SOURCES = \
	BookManager.cpp\
	Main.cpp \
	TextBox.cpp \
	ViewManager.cpp \
	View/AddView.cpp \
	View/ConfirmModalView.cpp \
	View/Constants.cpp \
	View/EditModalView.cpp \
	View/ListView.cpp \
	View/MainView.cpp \
	View/ModifyViewBase.cpp \
	View/RemoveView.cpp \
	View/SearchView.cpp \
	View/SelectViewBase.cpp \
	View/UpdateView.cpp

DIRS = build build/obj build/obj/View

CXXFLAGS = -std=c++17 -g

OUTPUT = book

.PHONY: prepare

build/obj/%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) $(CFLAGS) -c -o $@ $<

$(OUTPUT): $(SOURCES:%.cpp=build/obj/%.o)
	$(CXX) -MD -o $@ $^

prepare:
	mkdir -p $(DIRS)

clean:
	rm -rf $(OUTPUT) $(SOURCES:%.cpp=build/obj/%.o)

-include $(SOURCES:%.cpp=build/obj/%.d)
