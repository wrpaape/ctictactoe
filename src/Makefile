include $(MAKEFILE_SCAFFOLD)

define RULES
$(call USER_BINARY,tictactoe)
$(call TEST_BINARY,tictactoe)
endef

$(eval $(RULES))

all: $(TARGETS)

clean:
	$(RM) $(RM_FLAGS) $(TARGETS)
