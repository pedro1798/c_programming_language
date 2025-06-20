# Simple Makefile with use of gcc
CC=gcc # C Compiler 
CFLAGS=-g -Wall # Debug information 추가, Warning을 전부 표시 
EXE=hello # 최종 결과물 출력하는 rule
OBJ:=pointer_example.o structure_example.o

# 기본 빌드
all: $(EXE) # all rule은 EXE macro가 dependency로 충족되었을 때 실행된다.

$(EXE): $(OBJ) # 등록한 모든 오브젝트 파일을 디펜던시로 받는다.
	$(CC) ($OBJ) -o $(EXE) # 모든 오브젝트를 하나의 $(EXE) 실행 파일로 묶는다.

# %는 패턴 규칙에서 자리를 지정하는 와일드 카드
# $*는 그 %에 실제로 들어온 값을 의미한다. 
clean-%:
	rm -rf $*.o $*

# 실행 파일 생성(GNU 패턴 규칙 사용)
%: %.o  # %.o dependency 없다면 아래 rule에서 찾아 자동으로 실행한다.
	$(CC) $< -o $@
# $<: 첫 번쨰 디펜던시, $@: 타겟(rule, 만들고자 하는 결과물) 

# 오브젝트 파일 생성
%.o: %.c
	$(CC) $(CFLAGS) -c $<
