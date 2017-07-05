.PHONY: clean All

All:
	@echo "----------Building project:[ Week1_opdracht1 -  ]----------"
	@cd "Week1_opdracht1" && "$(MAKE)" -f  "Week1_opdracht1.mk"
clean:
	@echo "----------Cleaning project:[ Week1_opdracht1 -  ]----------"
	@cd "Week1_opdracht1" && "$(MAKE)" -f  "Week1_opdracht1.mk" clean
