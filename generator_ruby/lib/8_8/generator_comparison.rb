require "./generator.rb"

class GeneratorComparison < Generator
 
 attr_accessor :test_title
 
 def initialize test_file_name
  init_generator() 
  @test_file_name = "#{@path_to_tests_folder}/#{test_file_name}"
  @no_of_operands = 2
  @test_title = "Comparison test"
  @type_of_operands = "FIXED POINT BINARY"
  @type_of_result = "INTEGER"
 end
 
 def generate_test test_no , equal
   test = {}
   test["test_no"] = test_no
   t1 = @gen.generate_fixed_point_8_8
   
   if equal
     t2 = t1
   else
     t2 = @gen.generate_fixed_point_8_8
   end 
   
   test["first_operand"] = t1
   test["second_operand"] = t2
   n1 = @util.signed_binary_to_float(t1)
   n2 = @util.signed_binary_to_float(t2)
   r = ((n1==n2) ? 0 : ((n1>n2)? 1 : -1))
   test["result"] = r
   return test
 end
 
 def make_tests
   write_metadata()
   (0..100).each do |k|
      test_hash = generate_test(k,false)
      write_test(test_hash)
   end
   (0..10).each do |k|
      test_hash = generate_test(k,true)
      write_test(test_hash)
   end
  end
 
end

gen = GeneratorComparison.new("8_8/comparison.test");
gen.make_tests()