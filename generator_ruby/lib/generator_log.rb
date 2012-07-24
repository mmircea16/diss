require "./generator.rb"


class GeneratorLog < Generator
 
 attr_accessor :test_title
 
 def initialize options
   init_generator() 
   @test_file_name = "#{@path_to_tests_folder}/#{options["test_file_name"]}"
   @no_of_operands = 1
   @test_title = options["title"];
   @type_of_result = "FIXED POINT BINARY"
   @type_of_operands = "FIXED POINT BINARY"
   @operand_type = options["type"];
  end
 
 def generate_test test_no
     test = {}
     test["test_no"] = test_no
     case @operand_type
     when "8_8":
       k = "0"+@gen.generate_fixed_point(7,8)
     when "16_16":
       k = "0"+@gen.generate_fixed_point(15,16)   
     when "8_24":
       k = "0"+@gen.generate_fixed_point(7,24)
     when "24_8":
       k = "0"+@gen.generate_fixed_point(23,8)
     end
     
     test["first_operand"] = k
     n = @util.signed_binary_to_float(k)
     
     case @operand_type
     when "8_8":
       rez = @util.float_to_signed(Math.log(n),8,8)
     when "16_16":
       rez = @util.float_to_signed(Math.log(n),16,16)
     when "8_24":
       rez = @util.float_to_signed(Math.log(n),8,24);
     when "24_8":
       rez = @util.float_to_signed(Math.log(n),24,8);
     end
     
     test["result"] = rez
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
