require "../generator.rb"


class GeneratorFloor < Generator
 
 attr_accessor :test_title
 
 def initialize test_file_name
  init_generator() 
  @test_file_name = "#{@path_to_tests_folder}/#{test_file_name}"
  @no_of_operands = 1
  @test_title = "Integer part test"
  @type_of_result = "INTEGER"
  @type_of_operands = "FIXED POINT BINARY"
 end
 
 def generate_test test_no
   test = {}
   test["test_no"] = test_no
   k = @gen.generate_fixed_point_8_8
   test["first_operand"] = k
   test["result"] = @util.signed_binary_to_float(k).floor
   return test
 end
 
 def make_tests
  write_metadata()
  (0..100).each do |k|
     test_hash = generate_test(k)
     write_test(test_hash)
  end
 end

end

gen = GeneratorFloor.new("8_8/floor.test");
gen.make_tests()