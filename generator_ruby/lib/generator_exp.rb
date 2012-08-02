require "./generator.rb"


class GeneratorExp < Generator
 
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
       k = @gen.generate_fixed_point(3,8)
       k = k[0...1]*5+k
     when "16_16":
       k = @gen.generate_fixed_point(4,16)
       k = k[0...1]*12+k   
     when "8_24":
       k = @gen.generate_fixed_point(3,24)
       k = k[0...1]*5+k
     when "24_8":
       k = @gen.generate_fixed_point(5,8)
       k = k[0...1]*19+k        
     end
     
     test["first_operand"] = k
     n = @util.signed_binary_to_float(k)
     
     case @operand_type
     when "8_8":
       rez = @util.float_to_signed(Math.exp(n),8,8)
     when "16_16":
       rez = @util.float_to_signed(Math.exp(n),16,16)
     when "8_24":
       rez = @util.float_to_signed(Math.exp(n),8,24);
     when "24_8":
       rez = @util.float_to_signed(Math.exp(n),24,8);
     end
     
     test["result"] = rez
     return test
   end
 
 def make_tests
  write_metadata()
  (0..1000).each do |k|
     test_hash = generate_test(k)
     write_test(test_hash)
  end
 end

end
