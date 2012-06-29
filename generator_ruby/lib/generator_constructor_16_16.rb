require "./generator.rb"


class GeneratorConstructor1616 < Generator
 
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
   k = @gen.generate_float(-2**32,2**32-1)*1.0/(2**16)
   test["first_operand"] = k
   test["result"] = @util.float_to_signed_16_16(k)
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

gen = GeneratorConstructor1616.new("constructor16_16.test");
gen.make_tests()