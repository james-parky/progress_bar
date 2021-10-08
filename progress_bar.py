'''Module for printing custom progress bars'''

__author__ = "James Parkington"
__license__ = "Public Domain"
__version__ = "1.2"

_TARGET_COLOUR = '\33[31m'
_BASE_COLOUR = '\33[0m'
_FILLED_TICK = '█'
_EMPTY_TICK = '-'


class _Increment():
    def __get__(self, obj, obj_type=None):
        return self.value

    def __set__(self, obj, value):
        if not isinstance(value, int):
            raise TypeError('Increment must be of type \'int\'.')
        if value not in [1, 2, 5]:
            raise ValueError('Increment must be equal to 1, 2 or 5.')
        self.value = value


class _Target():
    def __get__(self, obj, obj_type=None):
        return self.value

    def __set__(self, obj, value):
        if not isinstance(value, int):
            raise TypeError('Target must be of type \'int\'.')
        if value < 0 or value > 100:
            raise ValueError('Target must be an integer in the range 0-100.')
        self.value = value


class _Annotation():
    def __get__(self, obj, obj_type=None):
        return self.value

    def __set__(self, obj, value):
        if not isinstance(value, bool):
            raise TypeError('Annotation must be of type \'bool\'.')
        self.value = value


class _Percentage():
    def __get__(self, obj, obj_type=None):
        return self.value

    def __set__(self, obj, value):
        if type(value) not in [int, float]:
            raise TypeError(
                'Percentage value must be of type \'int\' or \'float\'.')
        if value < 0 or value > 100:
            raise ValueError(
                'Percentage must be an integer or float in the range 0-100.')
        self.value = value


class ProgressBar():
    '''Custom progress bar class'''

    increment = _Increment()
    target = _Target()
    annotation = _Annotation()
    percentage = _Percentage()

    def __init__(self, increment=2, target=100, annotation=True, percentage=0):
        self.increment = increment
        self.target = target
        self.annotation = annotation
        self.percentage = percentage

    def draw(self):
        '''Print the progress bar to terminal'''
        progress_bar = [_EMPTY_TICK] * (100 // self.increment)
        int_percentage = int(self.percentage)
        rounded_percentage = int_percentage - (int_percentage % self.increment)
        num_filled_ticks = rounded_percentage // self.increment

        for i in range(num_filled_ticks):
            progress_bar[i] = _FILLED_TICK

        rounded_target = self.target - (self.target % self.increment)
        progress_bar[(rounded_target //
                     self.increment)-1] = f'{_TARGET_COLOUR}{_FILLED_TICK}{_BASE_COLOUR}'

        bar_string = ''.join(progress_bar)
        if self.annotation is True:
            print(f'|{bar_string}| {self.percentage}%')
        else:
            print(f'|{bar_string}|')
