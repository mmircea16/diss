require "./generator.rb"

class GeneratorSubtract < Generator
 
 attr_accessor :test_title
 
 def initialize test_file_name
  @test_file_name = test_file_name
  @no_of_operands = 2
  @test_title = "Non-saturated subtract test"
  @type_of_operands = "FIXED POINT BINARY"
  @type_of_result = "FIXED POINT BINARY"
  init_generator()
 end
 
 def generate_test test_no
   test = {}
   test["test_no"] = test_no
   t1 = @gen.generate_fixed_point_8_8
   t2 = @gen.generate_fixed_point_8_8
   test["first_operand"] = t1
   test["second_operand"] = t2
   r = (@util.signed_binary_to_float(t1)-@util.signed_binary_to_float(t2)) % (2**8)
   test["result"] = @util.float_to_signed_8_8(r)
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

gen = GeneratorSubtract.new("../tests/gen/subtract.test");
gen.make_tests()