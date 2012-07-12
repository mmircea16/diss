require "./generator.rb"


class GeneratoCastTo88 < Generator
 
 attr_accessor :test_title
 
 def initialize test_file_name
  init_generator() 
  @test_file_name = "#{@path_to_tests_folder}/#{test_file_name}"
  @no_of_operands = 1
  @test_title = "Cast 16.16 to 8.8"
  @type_of_result = "FIXED POINT BINARY"
  @type_of_operands = "FIXED POINT BINARY"
 end
 
 def generate_test test_no
   test = {}
   test["test_no"] = test_no
   k = @gen.generate_fixed_point(16,16)
   test["first_operand"] = k
   test["result"] = @util.cast_16_16_to_8_8(k)
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

gen = GeneratoCastTo88.new("16_16/cast_to_8_8.test");
gen.make_tests()