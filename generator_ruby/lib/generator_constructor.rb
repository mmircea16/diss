require "./generator.rb"


class GeneratorConstructor < Generator
 
 attr_accessor :test_title
 
 def initialize test_file_name
  init_generator() 
  @test_file_name = "#{@path_to_tests_folder}/#{test_file_name}"
  @no_of_operands = 1
  @test_title = "Constructor test"
  @type_of_result = "FIXED POINT BINARY"
  @type_of_operands = "FLOATING POINT"
 end
 
 def generate_test test_no
   test = {}
   test["test_no"] = test_no
   k = @gen.generate_float(-128,127)
   test["first_operand"] = k
   test["result"] = @util.float_to_signed_8_8(k)
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

gen = GeneratorConstructor.new("8_8/constructor.test");
gen.make_tests()