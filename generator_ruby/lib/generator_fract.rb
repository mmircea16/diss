require "./generator.rb"


class GeneratorFract < Generator
 
 attr_accessor :test_title
 
 def initialize test_file_name
  init_generator() 
  @test_file_name = "#{@path_to_tests_folder}/#{test_file_name}"
  @no_of_operands = 1
  @test_title = "Fractional part test"
  @type_of_result = "FIXED POINT BINARY"
  @type_of_operands = "FIXED POINT BINARY"
 end
 
 def generate_test test_no
   test = {}
   test["test_no"] = test_no
   k = @gen.generate_fixed_point_8_8
   test["first_operand"] = k
   n = @util.signed_binary_to_float(k)
   puts n
   puts @util.float_to_signed_8_8(n)
   puts n-n.floor
   puts @util.float_to_signed_8_8(n-n.floor)
   test["result"] = @util.float_to_signed_8_8(n-n.floor)
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

gen = GeneratorFract.new("fractional.test");
gen.make_tests()
