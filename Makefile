Name := FlameIDE

override CC := g++-4.7

ifdef BUILD
override TypeBuild := $(BUILD)
else
override TypeBuild := Release
endif

BuildPath := $(TypeBuild)

DepPath := $(BuildPath)/dep
ObjPath := $(BuildPath)/obj
BinPath := $(BuildPath)/bin
LibPath := $(BuildPath)/lib

Dirs := $(DepPath) $(ObjPath) $(BinPath) $(LibPath) $(TypeBuild)

override Libs :=

override Warn_flags := -Wall -Wextra #-Werror
#override Warn_flags := \
#			-Wall \
#			-Wextra \
#			-Wconversion \
#			-Werror \
#			-Winit-self \
#			-Wunreachable-code \
#			-Wformat=2 \
#			-Wswitch-default \
#			-Wtrigraphs \
#			-Wstrict-overflow=4 \
#			-Wfloat-equal \
#			-Wundef \
#			-Wshadow \
#			-Wcast-qual \
#			-Wcast-align \
#			-Wwrite-strings \
#			-Wlogical-op

Defines_Debug := -DDEBUG=1
Defines_Release :=

override Flags_Debug := -pg -O0 $(Warn_flags)
override Flags_Release := -O2 $(Warn_flags)

ifeq ($(TypeBuild),Release)
override Defines := $(Defines_Release)
override Flags := -std=c++11 -pipe $(Defines_Release) $(Flags_Release)
endif

ifeq ($(TypeBuild),Debug)
override Defines := $(Defines_Debug)
override Flags := -std=c++11 -pipe $(Defines_Debug) $(Flags_Debug)
endif

Path := ./src

# список всех ресурсных файлов
Sources := \
	$(subst ./,,$(shell find $(Path) -name *.cpp | grep -v Tests/ | grep -v Others/ ))


# получаем имена объектных файлов
Dependences := \
	$(addprefix $(DepPath)/,$(subst /,_,$(Sources:.cpp=.d)))
Flag_Deps := -MM -c


# файлы для модульного тестирования
Sources_Test := \
	$(subst ./,,$(shell find $(Path) -name *.cpp | grep Tests/ ))


Objects := \
	$(addprefix $(ObjPath)/,$(subst /,_,$(Sources:.cpp=.o)))
Flag_Obj := -fPIC
Flag_Lib := -shared


Target_lib := $(LibPath)/lib$(Name).so
Target_lib_static := $(LibPath)/lib$(Name).a
Target_bin_test := $(BinPath)/test_$(Name)

Path_ALL := \
	$(shell find $(Path) -type d)

#--------------------
all: .mkdirs .depends .compile .link
#--------------------
.mkdirs:
	@mkdir -p $(Dirs)
#--------------------
#
# Для описания зависимостей от заголовков
#
.depends: .mkdirs .make_depends
.make_depends: $(Dependences)

# честно говоря, такой вариант не очень нравится. Надо думать.
$(DepPath)/%.d :
	$(CC) $(Flags) $(Flag_Deps) $(Libs) $(subst _,/,$(notdir $(subst .d,.cpp,$@))) > $@
include $(wildcard $(DepPath)/*.d)
#--------------------
#
# Для компиляции объектных файлов
#
.compile : .depends $(Objects)

# $(Objects): obj/%.o : %.cpp # старый вариант; оставил для понимания происходящего
$(ObjPath)/%.o :
	$(CC) $(Flags) $(Flag_Obj) $(Libs) -c $(subst _,/,$(notdir $(subst .o,.cpp,$@))) -o $@

#--------------------
#
# Для сборки статичной и динамической библиотек
#
.link: .compile .link_libs .link_test

.link_libs: \
	$(Target_lib)
# 	$(Target_lib_static)

# видно с коммандной строки
$(Target_lib): $(Objects)
	$(CC) $(Flag_Lib) $(Flags) $(Libs) $(Objects) -o $(Target_lib)

# видно с коммандной строки
# ./lib/$(Target_lib_static): $(Objects)
# 	@ar rv lib/$(Target_lib_static) $(Objects)

.link_test: .compile $(Target_bin_test)

# видно с коммандной строки
$(Target_bin_test): .compile .link_libs
	$(CC) $(Flags) $(Defines) $(Target_lib) $(Sources_Test) -o $(Target_bin_test)
#--------------------
exec_test:
	./$(Target_bin_test)
#--------------------
#
# Для установки $(Name) как библиотеки
#
# Есть мысля заделать аналогично с компиляцией
# Разница лишь в том, что тут будет копирование
# заголовков в директорию /usr/include/$(Name)
# и динамической библиотеки в директорию /usr/lib/$(Name)
#
# install: .install_headers .install_lib
# 	
# .install_headers:
# 	
# .install_headers_mkdirs:
# 	@cd /usr/include; mkdir -p $(dir $(Headers))
# 
# 
# 	
# .install_lib:
# 	@mkdir /usr/lib/$(Name)
# 	@cp ./libs/$(Target_lib) /usr/lib/$(Name)
# 	
#--------------------
#
# Для удаления всех установленных файлов
#
# uninstall:
# 	
#--------------------
#
# Для дебианизации
#
# Это напоследок поиграться и поиздеваться над
# своими мозгами.
#
#.debianize:
#--------------------
.PHONY: clean
	
clean:
	@rm -rf $(Dirs)
#--------------------
