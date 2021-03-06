require "./generator.rb"

class GeneratorSaturatedMultiply < Generator
 
 attr_accessor :test_title
 
 def initialize test_file_name
  init_generator() 
  @test_file_name = "#{@path_to_tests_folder}/#{test_file_name}"
  @no_of_operands = 2
  @test_title = "Saturated multiply test"
  @type_of_operands = "FIXED POINT BINARY"
  @type_of_result = "FIXED POINT BINARY"
 end
 
 def generate_test test_no
   test = {}
   test["test_no"] = test_no
   t1 = @gen.generate_fixed_point_8_8
   t2 = @gen.generate_fixed_point_8_8
   test["first_operand"] = t1
   test["second_operand"] = t2
   r = (@util.signed_binary_to_float(t1)*@util.signed_binary_to_float(t2)) 
   if r >= 2**7
     r = 2**7 - 2**(-8)
   end
   if r < -2**7
       r = -2**7
   end
   test["result"] = @util.float_to_signed_8_8(r)
   return test
 end
 
 def make_tests
   write_metadata()
   (0..100% (2**8)).each do |k|
      test_hash = generate_test(k)
      write_test(test_hash)
   end
  end
 
end

gen = GeneratorSaturatedMultiply.new("8_8/saturated_multiply.test");
gen.make_tests()