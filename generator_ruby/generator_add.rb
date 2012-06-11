class GeneratorAdd<Generator
 
 attr_accessor :test_title
 
 def initialize test_file_name
  @test_file_name = test_file_name
  @no_of_operands = 2
  @test_title = "Add test"
  @type_of_operands = "FIXED POINT BINARY"
  @type_of_result = "FLOATING POINT"
 end
 
 def generate_test test_no
   test_hash = {}
   test["test_no"] = test_no
   
 end
 
 
end